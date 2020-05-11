#ifndef  __JSON_H__129
#define  __JSON_H__129
#include <stdio.h>
#include <stdbool.h>

#define prl { printf("\n"); }

//
//CONSTRUCTION DU TYPE 
//

typedef enum{
  JSON_NULL,
  JSON_BOOLEAN,
  JSON_NUMBER,
  JSON_STRING,
  JSON_ARRAY,
  JSON_OBJECT
} json_type_t;

typedef struct json_array_s{
	struct json_element_s **json_array ;
	size_t len ;
}json_array_t;

typedef struct json_number_s {
	enum{ Lng , Dble } type_number ; 
	union {
		long int lngi ;
		double dble ;
	} value_number ; 
}json_number_t;

typedef struct jsonlist_node {
    char* key;
    struct json_element_s* value_o;
    struct jsonlist_node* succ;
    
 } jsonlist_node;

typedef jsonlist_node* list_json;
typedef struct json_element_s {
	json_type_t type_e;    
	union {
		void* Null 	; 
	 	bool Bool;
	 	json_number_t Number;  
	 	char* String ; 
	 	json_array_t Array ; 
	 	list_json Object ; 
	} value_element;

}json_element_t;

//
//
//
json_type_t json_type( const json_element_t* e);

#define json_null()  (json_element_t*)NULL
//Boolean
json_element_t* json_boolean(bool b) ; 
bool  json_as_boolean(const json_element_t* e);

//Numbers
json_element_t* json_integer(long i ) ;
json_element_t* json_double(double d) ; 
bool json_is_integer (const json_element_t* e);
bool json_isdouble(const json_element_t* e);
long json_as_integer(const json_element_t* e);
double json_as_double(const json_element_t* e);


//STRINGS 

json_element_t* json_string(const char* s);
const char* json_as_string(const json_element_t* e);

//Array 

json_element_t* json_array();
json_element_t* json_array_get (const json_element_t* e, size_t i);
void json_array_set(json_element_t* e , size_t i , json_element_t* se);


//Object 

json_element_t* json_object() ; 
json_element_t* json_object_get(const json_element_t* e ,  const char* key);
void json_object_set(json_element_t* e , const char* key , json_element_t* value );

//Destroyer

void json_free(json_element_t* e);

//INPUT OUTPUT

  //EXPORT

void json_put (FILE* fd, const json_element_t* e );
void json_save(const char* fname , json_element_t* e);
  //IMPORT

json_element_t* json_get(FILE* fd) ; 
char next_char(FILE* fd);
void check_next_char(FILE* fd, char c );
bool is_next_char (FILE* fd,char c , bool cons );
void check_next_word(FILE* fd , const char* w);
char*  next_string(FILE* fd );
char* next_digits(FILE* fd);
json_element_t* json_load(const char* fname);


#endif 