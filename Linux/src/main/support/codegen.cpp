#include <iostream>

#include "defines/CodeGen.h"

using namespace llvm;

CodeGen::CodeGen() : m_context(), m_module("KrxkCompiler", m_context), m_builder(m_context)
{
    // KrxkCompiler 模块内部创建 main 函数
    auto funcType = FunctionType::get(m_builder.getInt32Ty(), false);
    auto function = Function::Create(funcType, Function::ExternalLinkage, "main", m_module);

    // main 函数内部创建 entry 基本块
    auto bb = BasicBlock::Create(m_context, "entry", function);

    // 设置后续指令序列插入到 entry 基本块中
    m_builder.SetInsertPoint(bb);
}

CodeGen::~CodeGen() = default;

Value *CodeGen::helpGenerateIR(const Node *node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    switch (node->nodeType)
    {
    case NodeType::OP:
    {
        auto left = helpGenerateIR(node->left);
        auto right = helpGenerateIR(node->right);

        if (left == nullptr || right == nullptr)
        {
            std::cerr << "Invalid Expression" << std::endl;
            return nullptr;
        }

        switch (node->op_val)
        {
        case 1: // +
            return m_builder.CreateAdd(left, right, "addtmp");
        case 2: // -
            return m_builder.CreateSub(left, right, "subtmp");
        default:
            std::cerr << "Unknown operator" << std::endl;
            return nullptr;
        }
    }
    break;
    case NodeType::NUMBER:
        return m_builder.getInt32(node->num_val);
    default:
        std::cerr << "Unknown node type" << std::endl;
        return nullptr;
    }
}

void CodeGen::generateIR(const Node *root)
{
    auto res = helpGenerateIR(root);
    m_builder.CreateRet(res);
}

void CodeGen::printResult()
{
    std::error_code EC;
    raw_fd_ostream file("output_IR.txt", EC);

    if (EC)
    {
        errs() << "Error opening file: " << EC.message() << "\n";
        return;
    }

    m_module.print(file, nullptr);

    file.close();
}