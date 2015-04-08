/*  Tim Strawbridge
 *  CS 23001
 *  4/6/15
 *  Stack, Part 2
 */

#include "string.hpp"
#include "stack.hpp"
#include <fstream>


//prototype free function to convert infix to postfix
void noOutInfToPre(std::ifstream&);
void outInfToPre(std::ifstream&, std::ofstream&);

int main(int argc, char *argv[]){

  //if no output file specified
  if (argc == 2){

    //infix file is second item on command line
    std::ifstream infix(argv[1]);

    noOutInfToPre(infix);

    infix.close();

  }
  else if (argc == 3){

    //infix file is second item on command line
    std::ifstream infix(argv[1]);

    //postfix file is third item
    std::ofstream outputPost(argv[2]);

    outInfToPre(infix, outputPost);

    infix.close();
    outputPost.close();

  }
  else{
    std::cerr << "Too few or too many arguments on command line. Exiting." << std::endl;
    exit(1);
  }

}


//function implementation if no output file specified
void noOutInfToPre(std::ifstream& in){

  //postfix expression
  Stack<String> post;

  String lhs;
  String rhs;
  String oper;

  //stores infix expression
  char expression[5000];
  in.getline(expression, 5000);
  
  while (!in.eof()){
    //token is now the original expression
    String token = expression;
    std::vector<String> newToken = token.split(' ');


    int i = 0;

    do{

      //if token is end of parenthetical expression
      //push into post with right order
      if (newToken[i] == ")"){
        rhs = post.pop();
        oper = post.pop();
        lhs = post.pop();
        post.push(lhs + " " +  rhs + " " + oper);

      }
      else if (newToken[i] != "("){
        post.push(newToken[i]);
      }

      ++i;

    } while (newToken[i] != ";");

    std::cout << post << std::endl;
    in.getline(expression, 5000);


   }



}


//function implementation for specified output file
void outInfToPre(std::ifstream& in, std::ofstream& out){

  std::cerr << "out file" << std::endl;
  //postfix expression
  Stack<String> post;

  String lhs;
  String rhs;
  String oper;

  //stores infix expression
  char expression[5000];
  in.getline(expression, 5000);

  while (!in.eof()){
    std::cerr << "in while" << std::endl;
    //token is now the original expression

    String stringExp(expression);
    std::vector<String> token = stringExp.split(' ');

    unsigned long int i = 0;

 do{
      std::cerr << "in do while" << std::endl;
      //if token is end of parenthetical expression
      //push into post with right order
      if (token[i] == ")"){
        std::cerr << "in if" << std::endl;
        rhs = post.pop();
        oper = post.pop();
        lhs = post.pop();
        post.push(lhs + " " + rhs + " " + oper);
      }

      else if (token[i] != "("){
        std::cerr << "in else if" << std::endl;
        post.push(token[i]);
      }

      else if (token[i] == ";"){
        out << post << std::endl;
        post = Stack<String>();
      }

      ++i;

    } while (i <= token.size());

    in.getline(expression, 5000);

  }


}

  
