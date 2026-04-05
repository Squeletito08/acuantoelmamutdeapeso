/*
A period of a string is a prefix that can be used to generate the whole string by repeating the prefix. The last repetition may be partial. For example, the periods of abcabca are abc, abcabc and abcabca.
Find all period lengths of a string: 
*/
void Finding_Periods(string& s){
  int n = s.size();
  vector<int> z = Z_function(s);

  for (int i = 0; i < n; i++)
    if (z[i] == n - i)
      cout << i << " ";

  cout << n << endl;
}