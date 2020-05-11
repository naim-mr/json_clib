#include <stdlib.h>
#include <stdio.h>
#include "json.h"
 
 

 
int main() {
  json_element_t* e = NULL;
  e = json_null(); json_put(stdout, e); prl; json_free(e);
  e = json_boolean(true); json_put(stdout, e); prl; json_free(e);
  e = json_boolean(false); json_put(stdout, e); prl; json_free(e);
  e = json_integer(123456L); json_put(stdout, e); prl; json_free(e);
  e = json_double(123456.987654); json_put(stdout, e); prl; json_free(e);
  e = json_string("Un petit texte"); json_put(stdout, e); prl; json_free(e);
  e = json_array(); json_put(stdout, e); prl;
  json_array_set(e, 0, json_integer(1928374566L));
  json_array_set(e, 3, json_string("Un autre texte"));
  json_array_set(e, 1, json_boolean(false));
  json_put(stdout, e); prl; json_free(e);
  e = json_object(); json_put(stdout, e); prl;
  json_object_set(e, "key1", json_integer(1928374566L));
  json_object_set(e, "key2", json_string("Un autre texte"));
  json_object_set(e, "key3", json_boolean(false));
  json_object_set(e, "key2", json_string("Un texte de remplacement"));
  json_put(stdout, e); prl; json_free(e);
  prl;
  //test de fonction 

  //Test de succès
  /*FILE* fdesc = fopen("example.json","r");
  check_next_word(fdesc,"[");
  fseek(fdesc,0,SEEK_SET);
  check_next_char(fdesc,'[');
  fseek(fdesc,9,SEEK_SET);
  printf("is next char ? : %d\n", is_next_char(fdesc,'[',true ) );
  fseek(fdesc,10,SEEK_SET);
  printf("next char : %c\n",next_char(fdesc)); 
  fseek(fdesc,30,SEEK_SET);
  printf("next digits: %s\n", next_digits(fdesc) );
  fseek(fdesc,0,SEEK_SET);
  printf("next string : %s\n", next_string(fdesc));
  printf("next string : %s\n", next_string(fdesc));
  fclose(fdesc);
  */
  //Test d'échec 

  /*
  fdesc = fopen("example.json","r");
  check_next_word(fdesc,"projeàt[]");
  fseek(fdesc,0,SEEK_SET);
  check_next_char(fdesc,'o');
  fclose(fdesc);
  */
  FILE* fd = fopen("example.json", "r");
  e = json_get(fd);
  fclose(fd);
  json_put(stdout, e); prl;
  json_free(e);
  
  return EXIT_SUCCESS;
}