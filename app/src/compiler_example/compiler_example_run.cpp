#include <iostream>
#include <string>

#include <stack_compiler/compiler.hpp>
#include <compiler_example/rpn_example.hpp>

#define EXPBUF_SIZE (4096)

using namespace std;

void call_rpn(void) {
  RPNSymbolDBAdapter dbAdapter;
  RPNExpressionFactory expFactory;
  Compiler cc(dbAdapter, expFactory);
  
  char buffer[EXPBUF_SIZE];
  
  cin.getline(buffer, EXPBUF_SIZE);
  
  string mathtext(buffer);
  RPNExpression *expr;
  
  expr = dynamic_cast<RPNExpression *>(cc.compile(mathtext));
  
  cout << "rpn: " << expr->str << endl;
  
  delete expr;
}

void print_help() {
  cout << "help:" << endl;
  cout << "\trpn <expression>" << endl;
  cout << "\thelp" << endl;
  cout << "\texit" << endl;
}

int main(void) {
  string command;
  
  while(true) {
    try {
      cout << "scexample> ";
      cin >> command;
    
      if("rpn" == command) {
        call_rpn();
      } else if("help" == command) {
        print_help();
      } else if("exit" == command) {
        break;
      } else {
        cout << "Error: Undefined command <" << command << ">" << endl; 
      }
    } catch(int) {
      cout << "Error: some error happen" << endl;
    }
  }
  
  return 0;
}

