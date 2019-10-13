////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cmath>

namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

// TODO: if you need any free functions, add their definitions here.


    size_t split(const std::string &txt, std::vector<std::string> &strs, char ch) {
        size_t pos = txt.find(ch);
        size_t initialPos = 0;
        strs.clear();
        while (pos != std::string::npos) {
            strs.push_back(txt.substr(initialPos, pos - initialPos));
            initialPos = pos + 1;
            pos = txt.find(ch, initialPos);
        }
        strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
        return strs.size();
    }

    bool parseInt(std::string &str, int &value) {
        for (char i : str) {
            if (i > '9' || i < '0')
                return false;
        }
        value = std::stod(str);
        return true;
    }


//==============================================================================
// class PlusOp
//==============================================================================


    int PlusOp::operation(char op, int a, int b,
                          int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
    {
        if (op != '+')
            throw std::logic_error("Operation other than Plus (+) are not supported");

        // here we just ignore unused operands
        return a + b;
    }

    IOperation::Arity PlusOp::getArity() const {
        return arDue;
    }

//==============================================================================
// class DivOp
//==============================================================================

    int DivOp::operation(char op, int a, int b, int /*c*/) {
        if (op != '/')
            throw std::logic_error("Operation other than Plus (/) are not supported");
        if (b == 0) return INT_MAX * (a > 0 ? 1 : -1);
        return a / b;
    }

    IOperation::Arity DivOp::getArity() const {
        return arDue;
    }


//==============================================================================
// class SigChangeOp
//==============================================================================


    int SigChangeOp::operation(char op, int a, int /*b*/, int /*c*/) {
        if (op != '!')
            throw std::logic_error("Operation other than Plus (!) are not supported");
        return -a;
    }

    IOperation::Arity SigChangeOp::getArity() const {
        return arUno;
    }

//==============================================================================
// class PowOp
//==============================================================================


    int PowOp::operation(char op, int a, int b, int c) {
        if (op != '^')
            throw std::logic_error("Operation other than Plus (!) are not supported");
        return pow(a, b);
    }

    IOperation::Arity PowOp::getArity() const {
        return arDue;
    }

//==============================================================================
// class StackMachine
//==============================================================================


// TODO: put StackMachine methods implementation here


    void StackMachine::registerOperation(char symb, IOperation *oper) {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if (it != _opers.end())
            throw std::logic_error("An operation is alr. reg");
        _opers[symb] = oper;
    }

    IOperation *StackMachine::getOperation(char symb) {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if (it == _opers.end())
            return nullptr;
        return it->second;
    }

    int StackMachine::calculate(const std::string &expr, bool clearStack) {
        if (clearStack)
            _s.clear();

        std::vector<std::string> tokens;
        split(expr, tokens, ' ');

        for (std::string token : tokens) {
            int value;
            bool isInteger = parseInt(token, value);

            if (isInteger) {
                _s.push(value);
                continue;
            }
            if (token.size() == 1) {
                char op;
                if (op != '+' && op != '/' && op != '!' && op != '^')
                    throw std::logic_error("Can't parse string");
                IOperation *operation = getOperation(token[0]);

            }
            throw std::logic_error("Can't parse string");
        }
        return 0;
    }
} // namespace xi
