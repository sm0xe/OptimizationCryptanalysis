#include <string>
#include <iostream>

using namespace std;

string substitute(string orig, string key){
  string substituted(orig);
  for(int i=0; i<substituted.length(); i++){
    if(orig[i]>='A' && orig[i]<='Z'){
      substituted[i] = key[orig[i]-'A'];
    }
    else if (orig[i]>='a' && orig[i]<='z'){
      substituted[i] = (char) key[orig[i]-'a']+32;
    }
    else{
      substituted[i] = orig[i];
    }
  }
  return substituted;
}

bool test_substitutions(){
  string original_string("ABCDEFGHIJKLMNOPQRSTUVWXYZ'abcdefghijklmnopqrstuvwxyz");
  string substitute_key("XYZABCDEFGHIJKLMNOPQRSTUVW");
  string substituted_string = substitute(original_string,substitute_key);
  return(substituted_string=="XYZABCDEFGHIJKLMNOPQRSTUVW'xyzabcdefghijklmnopqrstuvw");
}
