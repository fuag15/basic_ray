
#ifndef Parser_h
#define Parser_h

#include "Vector.h"
#include "Point.h"
#include "Color.h"
#include <iostream>
#include <string>
#include <map>

class Camera;
class Background;
class Light;
class Material;
class Object;
class Scene;

class Parser {

  struct Token {
    enum type {
      end_of_file,
      integer, real, string,
      left_brace, right_brace,
      left_bracket, right_bracket,
      comma,
    };
    type token_type;
    std::string string_value;
    int integer_value;
    double real_value;
    int line_number;
    int column_number;
  };
  std::istream &input;
  int line_number;
  int column_number;
  Token next_token;
  Material *default_material;
  std::map< std::string, Material * > defined_materials;
  std::map< std::string, Object * > defined_objects;

  void throwParseException(
    const std::string &message ) ;

  void readNextToken();
  bool peek(
    const Token::type type );
  bool peek(
    const std::string &keyword );
  Token match(
    const Token::type type,
    const std::string &failure_message );
  Token match(
    const std::string &keyword,
    const std::string &failure_message );

  std::string parseString();
  bool parseBoolean();
  int parseInteger();
  double parseReal();
  Vector parseVector();
  Point parsePoint();
  Color parseColor();

  Camera *parseDOFCamera();
  Camera *parsePinholeCamera();
  Camera *parseCamera();

  Background *parseConstantBackground();
  Background *parseBackground();

  Light *parsePointLight();
  Light *parseLight();

  Material *parseLambertianMaterial();
  Material *parseMaterial();

  Object *parseGroupObject();
  Object *parsePlaneObject();
  Object *parseSphereObject();
  Object *parseMovingSphereObject();
  Object *parseObject();

  public:

  Parser(
    std::istream &input );

  Scene *parseScene(
    std::string &filename );

};

#endif
