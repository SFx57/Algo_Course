//87104242

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

struct PairHush {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2>& pair) const {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};


template <class T>
using FilterFunction = std::function<bool(const T&)>;

template <class VType = size_t, class EType = std::pair<VType, VType>>
class IteratorImpl {
  public:
    using iterator = IteratorImpl;
     
    IteratorImpl(
      VType v,
      typename std::vector<VType>::iterator begin, 
      typename std::vector<VType>::iterator end, 
      const FilterFunction<EType>& filter
    ) : v_(v), now_(begin), end_(end), filter_(filter) {
      if (now_ != end_) {
        now_edge_ = {v_, *now_};
        if (!filter_(now_edge_)) { ++*this; }
      }
    }
    
    IteratorImpl& operator++() {
      do {
        ++now_;
        if (now_ == end_) {
          return *this;
        }
        now_edge_ = {v_, *now_};
      } while (!filter_(now_edge_) && now_ != end_);
      return *this;
    }
    
    bool operator==(const IteratorImpl& other) const {
      return now_ == other.now_;
    }

    bool operator!=(const IteratorImpl& other) const {
      return now_ != other.now_;
    }

    IteratorImpl begin() const {
      return *this;
    }

    IteratorImpl end() const {
      return {v_, end_, end_, filter_};
    }

    const EType& operator*() {
      return now_edge_;
    }

  private:
    EType now_edge_;
    VType v_;
    typename std::vector<VType>::iterator now_;
    typename std::vector<VType>::iterator end_;
    const FilterFunction<EType>& filter_;
};

template <class VType = size_t, class EType = std::pair<VType, VType>, class WType = int64_t>
class Graph {
public:
  using VertexType = VType;
  using EdgeType = EType;
  using WeightType = WType;

  virtual size_t EdgeCount() = 0;
  virtual size_t VertexCount() = 0;
  virtual std::vector<VType> Vertexes() = 0;

  virtual typename std::vector<VType>::iterator NeighboursBegin(VType v) = 0;
  virtual typename std::vector<VType>::iterator NeighboursEnd(VType v) = 0;
  virtual IteratorImpl<VType, EType>  NeighboursIt(
    VType v, 
    const FilterFunction<EType>& filter) = 0;

  virtual ~Graph() = default;
  
};

template <class VType = size_t, class EType = std::pair<VType, VType>, class WType = int64_t>
class ListGraph : public Graph<VType, EType, WType> {
  public:
    ListGraph(
      const std::vector<VType>& vertexes, 
      const std::vector<std::pair<EType, WType>>& edges
    ) : vertexes_(vertexes), num_vertex_(vertexes.size()), num_edges_(edges.size()) {
      for (auto& vertex : vertexes) {
        //adjacency_lists_[vertex] = std::vector<VType>();
        // the line above breaks time limit
      }
      for (auto& edge : edges) {
        auto min = std::min(edge.first.first, edge.first.second);
        auto max = std::max(edge.first.first, edge.first.second);
        weights_[{min, max}] += edge.second;
        if (weights_[{min, max}] == 0) {
          adjacency_lists_[edge.first.first].push_back(edge.first.second);
        }
      }
    }

    size_t EdgeCount() override {
      return num_edges_;
    }

    size_t VertexCount() override {
      return num_vertex_;
    }

    typename std::vector<VType>::iterator NeighboursBegin(VType v) override {
      return adjacency_lists_[v].begin();
    }

    typename std::vector<VType>::iterator NeighboursEnd(VType v) override {
      return adjacency_lists_[v].end();
    }

    std::vector<VType> Vertexes() override {
      return vertexes_;
    }
    
    IteratorImpl<VType, EType> NeighboursIt(
      VType v, 
      const FilterFunction<EType>& filter
    ) override {
      return {v, NeighboursBegin(v), NeighboursEnd(v), filter};
    }

  protected:
    std::unordered_map<VType, std::vector<VType>> adjacency_lists_;
    std::unordered_map<EType, WType, PairHush> weights_;
    std::vector<VType> vertexes_;
    size_t num_vertex_;
    size_t num_edges_;
};

template <class VType = size_t, class EType = std::pair<VType, VType>, class WType = int64_t> 
class UndirectedListGraph : public ListGraph<VType, EType, WType> {
  public:
    using ListGraph<VType, EType, WType>::adjacency_lists_;
    using ListGraph<VType, EType, WType>::weights_;
    UndirectedListGraph(
      const std::vector<VType>& vertexes, 
      const std::vector<std::pair<EType, WType>>& edges
    ) : ListGraph<VType, EType, WType>(vertexes, edges) {
      for (auto& edge : edges) {
        auto min = std::min(edge.first.first, edge.first.second);
        auto max = std::max(edge.first.first, edge.first.second);
        if (weights_[{min, max}] == 0) {
          adjacency_lists_[edge.first.second].push_back(edge.first.first);
        }
      }
    }
};

template <class VType = size_t, class EType = std::pair<VType, VType>, class WType = int64_t>
class SNP : public UndirectedListGraph<VType, EType, WType> {
  public:
    SNP(
      const std::vector<VType>& vertexes, 
      const std::vector<std::pair<EType, WType>>& edges
    ) : UndirectedListGraph<VType, EType, WType>(vertexes, edges) {
      parent_ = vertexes;
      big_weight_.resize(vertexes.size());
      order_.resize(vertexes.size());

    }

    VType CalcPar(VType v) {
      if (v == parent_[v]) {
        return v;
      }
      parent_[v] = CalcPar(parent_[v]);
      return parent_[v];
    }

    void Append(VType s_0, VType t_0, WType w) {
      --s_0;
      --t_0;
      auto s = CalcPar(s_0);
      auto t = CalcPar(t_0);

      if (s == t) {
        s_0 = CalcPar(s_0);
        big_weight_[s_0] += w;
        return;
      }
      if (order_[s] < order_[t]) {
        std::swap(s, t);
      }
      parent_[t] = s;
      if (order_[s] == order_[t]) {
        ++order_[s];
      }
      big_weight_[s] += big_weight_[t];
      s_0 = CalcPar(s_0);
      big_weight_[s_0] += w;
    }

    WType GetWeight(VType s) {
      --s;
      return big_weight_[CalcPar(s)];
    }

  protected:
    std::vector<VType> parent_;
    std::vector<WType> big_weight_;
    std::vector<VType> order_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  size_t n;
  size_t m;
  std::cin >> n >> m;
  std::vector<size_t> vertexes(n);
  for (size_t i = 0; i != n; ++i) {
    vertexes[i] = i;
  }
  std::vector<std::pair<std::pair<size_t, size_t>, int64_t>> edges;

  SNP<size_t> snp(vertexes, edges);

  size_t code;
  size_t x;
  size_t y;
  int64_t w;
//
  for (size_t i = 0; i != m; ++i) {
    std::cin >> code;
    if (code == 1) {
      std::cin >> x >> y >> w;
      snp.Append(x, y, w);
      continue;
    }
    std::cin >> x;
    std::cout << snp.GetWeight(x) << "\n";
  }

  return 0;
}
