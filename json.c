#include "json.h"
#include <stdlib.h>
#include <string.h>
#define error(mess,code) {fprintf(stderr,"err: %s\n",mess); exit(code);}

// Structure principale 
// Dans le header pour que le main compile .


//BOOLEANS 


 json_type_t json_type(const json_element_t* e){
        return e->type_e;
}
 

json_element_t* json_boolean(bool b){
 	json_element_t* ptr= (json_element_t*) malloc(sizeof(json_element_t)); 
 	if(ptr==NULL )error("--json_boolean :: malloc failed\n",EXIT_FAILURE);
 	json_element_t  njson;
 	njson.type_e = JSON_BOOLEAN;
 	njson.value_element.Bool= b ; 
  *ptr = njson;
	return ptr;
}


 bool json_as_boolean(const json_element_t* e){
  json_type_t tjson = json_type(e);
 	if(tjson!=JSON_BOOLEAN ) error("--json_as_boolean :: the element dosn'nt have the right type ",EXIT_FAILURE);
	return e->value_element.Bool;
}

//Number 

json_element_t* json_integer (long i ){
	json_element_t* temp=(json_element_t*) malloc(sizeof(json_element_t));
	if(temp==NULL)error("--json_integer :: malloc failed\n",EXIT_FAILURE);
	json_element_t nj ;
	nj.type_e= JSON_NUMBER;
	nj.value_element.Number.type_number= Lng;
	nj.value_element.Number.value_number.lngi= i ; 
	*temp=nj;
	return temp; 
}



json_element_t* json_double (double d ){
	json_element_t temp;	
	temp.type_e= JSON_NUMBER;
	temp.value_element.Number.type_number= Dble;
	temp.value_element.Number.value_number.dble= d ; 
	json_element_t* ptr=(json_element_t*) malloc(sizeof(json_element_t*));
	if(ptr==NULL)error("--json_double malloc :: failed\n",EXIT_FAILURE)
  *ptr=temp;
	return ptr ; 
}

bool json_is_integer (const json_element_t* e){
	json_type_t tjson = json_type(e);
	if(tjson!=JSON_NUMBER ) error("--json_is_integer :: the element dosn't have the right type ",EXIT_FAILURE);
	return (e->value_element.Number.type_number==Lng);
}


bool json_is_double (const json_element_t* e){
	json_type_t tjson = json_type(e);
	if(tjson!=JSON_NUMBER ) error("--json_is_double  :: the element dosn't have the right type ",EXIT_FAILURE);
	return (e->value_element.Number.type_number==Dble);
}


long json_as_integer(const json_element_t* e ){
	if(json_type(e)!=JSON_NUMBER) error("--json_as_integer :: the element dosn't have the right type ",EXIT_FAILURE);
 	if(json_is_integer(e)) {
 		long n = e->value_element.Number.value_number.lngi;
 		return n;
 	}
	double d =(double) e->value_element.Number.value_number.dble;
 	return d ; 
}


double json_as_double (const json_element_t* e ){
	if(json_type(e)!=JSON_NUMBER) error("--json_as_double :: the element dosn't have the right type ",EXIT_FAILURE);
 	if(json_is_double(e)) {
 		double d = e->value_element.Number.value_number.dble;
 		return d;
 	}
	long n =(long) e->value_element.Number.value_number.dble;
 	return n ; 
}

//STRING


json_element_t* json_string(const char* s){
	json_element_t* str=(json_element_t*)malloc(sizeof(json_element_t));
	if(str==NULL)error("--json_string :: malloc failed\n",EXIT_FAILURE);
  json_element_t njson;
	njson.type_e= JSON_STRING;
	njson.value_element.String = (char* ) malloc(strlen(s)+1);
	if(njson.value_element.String==NULL) error("--json_string :: malloc failed\n",EXIT_FAILURE);
	strcpy(njson.value_element.String,s );
	*str= njson;
  return str ; 
}
 

const char* json_as_string(const json_element_t* e){
	json_type_t tjson = json_type(e);
 	if(tjson!=JSON_STRING) error("--json_as_string :: the element dosn't have the right type ",EXIT_FAILURE);
 	const char* s = e->value_element.String;
 	return s ; 
}
//ARRAY 
json_element_t* json_array(){
	json_element_t* njson=malloc(sizeof(json_element_t*));
  if(njson==NULL)error("--json_array :: malloc failed\n",EXIT_FAILURE);
	njson->type_e= JSON_ARRAY; 
	njson->value_element.Array.json_array=NULL ; 
	njson->value_element.Array.len=0;
	return njson;

}



//ATTENTION: l'utilisateur devra prendre en compte que les cases du tableau sont numérottées de 0 à TailleDuTableau 
//EXEMPLE : NE PAS RENTRER 1 POUR LA CASE D'INDICE 0 MAIS BIEN 0!

json_element_t* json_array_get(const json_element_t* e, size_t i) {
	json_type_t tjson = e->type_e;
 	if(tjson!=JSON_ARRAY)  error("--json_array_get :: the element dosn't have the right type ",EXIT_FAILURE);
 	if(i>e->value_element.Array.len)  return json_null();
 	return e->value_element.Array.json_array[i-1]; 
 
}

	

// l'utilisateur devra prendre en compte que les cases du tableau sont numérottés de 0 à TailleDuTableau 
 void json_array_set(json_element_t* e, size_t i, json_element_t* se) {
 	json_type_t tjson = e->type_e;
 	if(tjson!=JSON_ARRAY) error("--json_array_set :: the element dosn't have the right type ",EXIT_FAILURE);
    size_t len = e->value_element.Array.len;
 	if(i==0  && len==0){
 		json_element_t** ptr_realloc =(json_element_t** )realloc(e->value_element.Array.json_array,sizeof(json_element_t*));
 		if(ptr_realloc==NULL) {
 		  error("--json_array_set ::realloc fail \n",EXIT_FAILURE);
 		}else{
 		  e->value_element.Array.json_array= ptr_realloc;
 		}
		e->value_element.Array.json_array[0]=se;
 		e->value_element.Array.len++;
 		return;		
 	}
 	if(i>len-1) {	
 	  json_element_t**ptr_real =(json_element_t**) realloc(e->value_element.Array.json_array, sizeof(json_element_t*)*(e->value_element.Array.len+(i-(len-1))));
 		if(ptr_real==NULL) {
 			error("--json_array_set ::realloc fail \n",EXIT_FAILURE);
 		}else{ 
 		  e->value_element.Array.json_array=ptr_real;
 		}
	  e->type_e=JSON_ARRAY;
	  size_t j ;
 		for(j=len; j<i;j++){
 			e->value_element.Array.json_array[j]=json_null();
 			e->value_element.Array.len++;
 		}	
		e->value_element.Array.json_array[i]=se;
 		e->value_element.Array.len++;
 		}
	if(i<=len-1 ) {
    json_free(e->value_element.Array.json_array[i]);
    e->value_element.Array.json_array[i]=se;
  }

}







//OBJECT

json_element_t* json_object(){
    json_element_t njson;
    njson.type_e= JSON_OBJECT ;
    njson.value_element.Object= (list_json) malloc(sizeof(jsonlist_node));
    if(njson.value_element.Object==NULL) error("--json_object() :: malloc failed",EXIT_FAILURE);
    njson.value_element.Object->key =NULL;
    njson.value_element.Object->value_o= NULL;
    njson.value_element.Object->succ=NULL;
    json_element_t *ptr =malloc(sizeof(json_element_t*));
    if(ptr==NULL) error("--json_object :: malloc failed",EXIT_FAILURE);
    *ptr=njson;
    return ptr ; 
}

json_element_t* json_object_get(const json_element_t* e, const char* key) {
  	json_element_t* temp =(json_element_t*) e;
  	if(json_type(e)!=JSON_OBJECT) error("--json_object_get :: the element dosn't have the right type ",EXIT_FAILURE);
  	while(temp->value_element.Object->succ != NULL ){
       if(strcmp(key ,temp->value_element.Object->key)==0) return (json_element_t*)temp->value_element.Object->value_o;
       temp->value_element.Object =  temp->value_element.Object->succ;
  	}
  	return json_null();	
  }

list_json create_node_json(const char* key , json_element_t* value){
 	jsonlist_node n;
 	n.key=(char*)malloc(strlen(key)+1);
 	if(n.key==NULL) error("malloc failed\n",EXIT_FAILURE);
 	strcpy(n.key,key) ;
 	n.value_o= value;
 	n.succ=NULL;
 	list_json nlist=malloc(sizeof(jsonlist_node));
 	if(nlist==NULL) error("malloc failed\n",EXIT_FAILURE);
 	*nlist=n;
 	return nlist;
}

void json_object_set(json_element_t* e, const char* key, json_element_t* value){
 	if(e->type_e!=JSON_OBJECT) error("--json_object_set :: the element dosn't have the right type ",EXIT_FAILURE);
  list_json temp=e->value_element.Object; 
  list_json l=temp;	
  if(temp->key == NULL ){
  	if(temp->value_o!=NULL)error("--json_object_set :: element without key ", EXIT_FAILURE);
  	temp->key=(char*)malloc(strlen(key)+1);
  	if(temp->key== NULL )error("--json_object_set :: malloc fail ", EXIT_FAILURE);
  	strcpy(temp->key,key);
  	temp->value_o=value;
  	temp->succ=NULL;
  	return ; 
  }
  while(temp!=NULL){
  	if(strcmp(key, temp->key )==0) { 
  		json_free(temp->value_o);
  	  temp->value_o = (json_element_t*)value; 
   		return ; 
  	}
  l=temp;
  temp=(list_json)temp->succ;
 	}
  l->succ= create_node_json(key,value);
   
}


// FREE
void json_free_object (list_json o){
	if(o==NULL) return ; 
	json_free_object((list_json)o->succ);
	free(o->key);
  o->key=NULL;
  json_free((json_element_t*)o->value_o);
  o->value_o=NULL;
  free(o);
  o=NULL;
}

void json_free(json_element_t* e ){
	if(e==json_null())return ;
	json_type_t tjson = e->type_e;
	switch(tjson){
		case JSON_NULL : break ; 
		
    case JSON_BOOLEAN :
    	e=NULL;
			break;
		
    case JSON_NUMBER:
			e=NULL;
			break;
		
    case JSON_STRING:
			free(e->value_element.String);
			e->value_element.String=NULL;
			free(e);
			e=NULL;
			break;
		
    case JSON_ARRAY : ;//this is an empty statement 
		    size_t i=0;
		    size_t len = e->value_element.Array.len;
   		 	for (;i<len; i++) {
   		 		json_free(e->value_element.Array.json_array[i]);
   		 		e->value_element.Array.json_array[i]=NULL;
   		 	}
   		 	free(e);
   		 	e=NULL;
   		 	break;
   	
    	case JSON_OBJECT :
      	json_free_object(e->value_element.Object);
   			free(e);
   			e=NULL;
   			break;

	}
}

//EXPORT 
void json_put(FILE* fdesc, const json_element_t* e){
	if(e==NULL){
		fprintf(fdesc, "\"null\"");
		return;
	}
	json_type_t tjson = e->type_e;
	switch(tjson){
		case JSON_NULL: break;
		case JSON_BOOLEAN :
		  if(json_as_boolean(e)) {
				fprintf(fdesc, "true");
			}else{
				fprintf((fdesc), "false");
			}
			break;
		
    case JSON_NUMBER :
			if(json_is_double(e))fprintf(fdesc, "%f",json_as_double(e));
			if(json_is_integer(e))fprintf(fdesc, "%ld",json_as_integer(e));
			break;
		
    case JSON_STRING:
			fprintf(fdesc, "%s",json_as_string(e));
			break;
		
    case JSON_ARRAY:
	    if(e->value_element.Array.len==0){
		     fprintf(fdesc,"[]");
		     break;
		    }
			fprintf(fdesc,"[ ");
			size_t i;
		  size_t len = e->value_element.Array.len;
		  for(i=0;i<len;i++) {
			 	json_put(fdesc,e->value_element.Array.json_array[i]);
			  if(i!=len-1) fprintf(fdesc, ",");
			 }
		  fprintf(fdesc,"]");
		  break;	
		
    case JSON_OBJECT:
		  if(e->value_element.Object->key==NULL){
		    fprintf(fdesc,"{} ");
		    break;
		    }
		  fprintf(fdesc,"\n{ ");
		  json_element_t* temp =(json_element_t*) e;
		  do{
				fprintf(fdesc, "%s : ",temp->value_element.Object->key);
        json_put(fdesc,temp->value_element.Object->value_o);
				temp->value_element.Object=(list_json)temp->value_element.Object->succ;
				if(temp->value_element.Object!=NULL) fprintf(fdesc, ",\n");
      }while(temp->value_element.Object!=NULL);
			fprintf(fdesc,"\n}");     
			break;
       
			
		}

	}

void json_save(const char* fname, json_element_t* e){
	FILE* fdesc = fopen(fname,"w+");
	json_put(fdesc,e);
	fclose(fdesc);
}




//IMPORT 



char next_char(FILE* fd) {
	if(fd==NULL) error("--next_char :: file is null",EXIT_FAILURE);
	int c;
	while(1){
		c=fgetc(fd);
		if(c==EOF) error("--next_char :: end of file \n", EXIT_FAILURE);
	    if(c!=' '&& c!='\n' &&c!='\r' && c!='\t') return c;
	}
}



 void check_next_char(FILE* fd , char c){
 	if(fd==NULL) error("--check_next_char :: file is null",EXIT_FAILURE);
 	if(next_char(fd)!= c) error("--check_next_char::",EXIT_FAILURE);

 }

bool is_next_char (FILE* fd,char c , bool cons ){
	if(fd==NULL) error("--is_next_char :: file is null",EXIT_FAILURE);
	char stk = next_char(fd);
	if(stk!=c ){
    cons=false;
    ungetc(stk,fd);
  }else if(stk==c && cons==false){
    ungetc(c,fd);
    cons=true ;
  } 
  return cons ; 
}


void check_next_word(FILE* fd, const char* w){
	if(fd==NULL) error("--check_newt_word :: file is null",EXIT_FAILURE);
	   size_t len = strlen(w);
     char* str = (char*) malloc(len+1);
     if(str==NULL)error("--check_next_word :: malloc failed",EXIT_FAILURE);
     int c;
     size_t i;
     for( i=0;i<len;i++){
     	c=fgetc(fd);
     	str[i]=c;
     }
     c=fgetc(fd);
     str[i]='\0';
     if(strcmp(str,w)!=0 ||(c!=' '&& c!='\n' &&c!='\r' && c!='\t' && c!=';'&& c!=','&& c!='.'&& c!='?'&& c!='!'&& c!=':') ) error("--check_next_word :: next word isn't w",EXIT_FAILURE);
     //ici on doit revenir d'un digit en arrière car le fgetc précedent est utilisé pour le test mais avance le curseurs d'un caractère ce qui peut fausser la suite
     fseek(fd,-1,SEEK_CUR);
     fprintf(fd, "%c\n",c );


}



    
char* next_string(FILE* fd){
	if(fd==NULL) error("--next_string :: file is null",EXIT_FAILURE);
	int c =fgetc(fd);
	while(c!='"'){ 
		c=fgetc(fd);
	}
	char* str=(char*) malloc(sizeof(char));
	if(str==NULL)error("--next_string :: malloc failed",EXIT_FAILURE);
	size_t j=0;
  str[0]=c;
  c=fgetc(fd);
  while(c!='"'){
   	if(c==EOF)break;
   	str=(char*)realloc(str,(j+1)*sizeof(char));
    if(str==NULL)error("--check_next_word :: realloc failed",EXIT_FAILURE);
  	j++;
    str[j]=c;
  	c=fgetc(fd);

  }
  j++; 
  str[j]=c;
  str[j+1]='\0';
  
  return str;
   
}

char* next_digits(FILE* fd){
	if(fd==NULL) error("--next_digits :: file is null",EXIT_FAILURE);
	size_t j=1;
	char * str =(char*)malloc(j);
	if(str==NULL)error("--next_digits :: malloc failed",EXIT_FAILURE);
	int c = fgetc(fd) ;
  while( c!='0'&& c!='1' && c!='2' && c!='3'&& c!='4' && c!='5' && c!='6' && c!='7' && c!='8'&& c!='9' && c!=EOF){
   	c=fgetc(fd);
  }
  while(  c=='0'||c=='1'||c=='2' ||c=='3'||c=='4' ||c=='5' ||c=='6' ||c=='7' || c=='8' || c=='9') {
  	str[j-1]=c;
  	j++;
  	str=(char*)realloc(str,j);
  	if(str==NULL)error("--next_digits :: realloc failed",EXIT_FAILURE);
  	c=fgetc(fd);
   }
   //ici on doit revenir d'un char en arrière car le fgetc précedent est utilisé pour le test mais avance le curseurs d'un caractère ce qui peut fausser la suite
   fseek(fd,-1,SEEK_CUR);
   fprintf(fd,"%c",c);
   str[j-1]='\0';

   return str;

}

json_element_t* json_load(const char* fname) {
 	FILE* fd= fopen(fname,"r");
 	return json_get(fd);
 }



json_element_t* json_get(FILE* fd) {
  int c = next_char(fd);
  if (c == 'n') {
   	ungetc(c,fd);
    check_next_word(fd,"null");
    return json_null();
  }
  if (c == 't') {
    ungetc(c,fd);
    check_next_word(fd,"true");
    return json_boolean(true);
  }
  if (c == 'f') {
    ungetc(c,fd);
    check_next_word(fd,"false");
    return json_boolean(false);
  }
  if (c == '-') {
    json_element_t* se = json_get(fd);
    if (json_type(se) != JSON_NUMBER) {
      fprintf(stderr, "A number is expected after character '-'\n");
      exit(EXIT_FAILURE);
    }
    if (json_is_double(se)) {
      double d = json_as_double(se);
      json_free(se);
      return json_double(-d);
    }
    if (json_is_integer(se)) {
      long i = json_as_integer(se);
      json_free(se);
      return json_integer(-i);
    }
  }
  if ('0' <= c && c <= '9') {
    
  	ungetc(c,fd);
    char* number = next_digits(fd);
    c = fgetc(fd);
     if (c == '.') {
      char* decimal = next_digits(fd);
      number = realloc(number, strlen(number) + strlen(decimal) + 2);
      strcat(number,".");
      strcat(number,decimal);
      json_element_t* e = json_double(strtod(number,NULL));
      free(number);
      free(decimal);
      return e;
    } else {
      ungetc(c,fd);
      json_element_t* e = json_integer(strtol(number,NULL,10));
      free(number);
      return e;

    }
   }
  if (c == '"') {
  	ungetc(c,fd);
    char* str = next_string(fd);
    json_element_t* e = json_string(str);
    free(str);
    return e;
  }
  if (c == '[') {
    json_element_t* e = json_array();
    size_t i = 0;
    if (is_next_char(fd,']',true)) return e;
    while(1) {
      json_element_t* se = json_get(fd);
      json_array_set(e,i++,se);
      c = next_char(fd);
      if (c == ']') return e;
      if (c != ',') {
      	fprintf(stderr, "1-Unexpected character '%c'; ']' or ',' excepted\n", c);
        exit(EXIT_FAILURE);

      }
    }
  }
  if (c == '{') {
    json_element_t* e = json_object();
    if (is_next_char(fd,'}',true)) return e;
    while(1) {
    
      check_next_char(fd,'"');
      ungetc('"',fd);
      char* key = next_string(fd);
      check_next_char(fd,':');
      json_element_t* value = json_get(fd);
      json_object_set(e,key,value);
      c = next_char(fd);
      if (c == '}') return e;
      if (c != ',') {
        fprintf(stderr, "2-Unexpected character '%c'; ']' or ',' excepted\n", c);
        exit(EXIT_FAILURE);
      }
    }
  }
  fprintf(stderr, "3-Unexpected character '%c'; 'n', 't', 'f', [0-9], '\"', '[' or '{' excepted\n", c);
  exit(EXIT_FAILURE);
}