#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include "obj/function.hpp"
#include "runtime.hpp"
#include "../tstring.hpp"

namespace Secundo
{
    class Functions
    {
    private:
        std::vector<Function> functions;

    public:
        void addFunction(const Function &f)
        {
            // std::cout << "ADD FUNCTION!!! " << f.getName() << std::endl;
            functions.push_back(f);
        }

        bool existsFunction(const std::string &func)
        {
            for (int i = 0; i < functions.size(); i++)
            {
                if (functions[i].getName() == func)
                {
                    return true;
                }
            }
            return false;
        }

        void runFunction(std::string func)
        {
            if (!existsFunction(func))
            {
                std::cout << "ERROR: FATAL_ERROR: Function " << func << " not found!" << std::endl;
                _quit(1);
            }

            std::vector<std::string> v = getFunction(func).getCode();

            for (int i = 0; i < v.size(); i++)
            {
                tri::string tmp = v[i];
                tmp = tmp.trim();

                std::string f = tmp.cxs().substr(1, tmp.length() - 1);

                if (tmp.at(0) == '&')
                {
                    runFunction(f);
                }
                else if (tmp.at(0) == '~')
                {
                    std::string fname = func + "_" + std::to_string(Secundo::Runtime.Index) + ".sh";

#ifdef _WIN32 || _WIN64
                    fname = func+"_"+std::to_string(Secundo::Runtime.Index)+".bat";
#endif

                    std::ofstream file_(fname);
                    file_ << f << std::endl;
                    std::string command = std::string("chmod +x ./" + fname + "; bash ./" + fname);

#ifdef _WIN32 || _WIN64
                    command = fname;
#endif

                    system(std::string(command + Secundo::Runtime.quiet).c_str());
                    Runtime.DeletingFiles.push_back(fname);
                }
                else system(std::string(v[i] + Secundo::Runtime.quiet).c_str());
            }
        }

        void clearFunctions()
        {
            functions.clear();
            functions = std::vector<Function>();
        }

        Function getFunction(std::string func)
        {
            if (!existsFunction(func))
            {
                printf(Secundo::Translation.get("50").c_str(), Runtime.LineNumber, func.c_str());
                _quit(1);
            }

            for (int i = 0; i < functions.size(); i++)
            {
                if (functions[i].getName() == func)
                {
                    return functions[i];
                }
            }

            return Function("[<NULL>]");
        }
    };
}

#endif
