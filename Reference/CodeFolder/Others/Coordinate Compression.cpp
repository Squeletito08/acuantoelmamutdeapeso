vector<int> coordinate_compression(vector<int>& coordinates){
  vector<int> compression(coordinates.size()); 
  vector<int> aux = coordinates;
  sort(aux.begin(), aux.end());
  aux.resize(unique(aux.begin(), aux.end()) - aux.begin());
  for (int i = 0; i < n; ++i){
    compression[i] = lower_bound(aux.begin(), aux.end(), coordinates[i]) 
    - aux.begin();
  }
  return compression; 
}