#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>

#include "node.h"

class CodeGen
{
private:
    llvm::LLVMContext m_context;
    llvm::Module m_module;
    llvm::IRBuilder<> m_builder;

public:
    CodeGen();
    ~CodeGen();

protected:
    llvm::Value* helpGenerateIR(const Node* node);
public:
    void generateIR(const Node *root);
    void printResult();
};