#include "util/FileOperations.h"

namespace TUNA
{
    namespace IO
    {
        std::string read_file(const std::string &filepath)
        {
            std::cout << std::string("Reading file: ") + filepath << std::endl;
            std::string result;
            std::ifstream in(filepath, std::ios::in | std::ios::binary);
            if (in)
            {
                in.seekg(0, std::ios::end);
                size_t size = in.tellg();
                if (size != -1)
                {
                    result.resize(size);
                    in.seekg(0, std::ios::beg);
                    in.read(&result[0], size);
                }
                else
                {
                    // handle failure to read from file
                    std::cout << "-1" << std::endl;
                }
            }
            else
            {
                // handle failure to open file
                std::cout << "-2" << std::endl;
            }

            return result;
        }
    } // namespace IO

} // namespace TUNA
