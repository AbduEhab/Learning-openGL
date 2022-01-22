#include "renderer/Shader.h"
#include "util/FileOperations.h"

namespace TUNA
{
    Shader::Shader(const std::string &name, const std::string &filepath) : _name(name), _filepath(filepath)
    {

        uint32_t program_id = glCreateProgram();
        _id = program_id;

        std::string file = IO::read_file(filepath);

        process_shaders(file);

        _vertex_shader = compile(GL_VERTEX_SHADER, _shader_source_code.vertex_shader);
        _fragment_shader = compile(GL_FRAGMENT_SHADER, _shader_source_code.fragment_shader);

        glAttachShader(program_id, _vertex_shader);
        glAttachShader(program_id, _fragment_shader);
        glLinkProgram(program_id);
        glValidateProgram(program_id);

        std::cout << _fragment_shader << std::endl;

        int success;

        glGetProgramiv(program_id, GL_LINK_STATUS, &success);
        if (!success)
        {
            int length;
            glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);

            char *message = (char *)alloca(length * sizeof(char));
            glGetProgramInfoLog(program_id, length, &length, message);
            printf("ERROR: SHADER_LINKING_FAILED\n '%s'", message);
            glDeleteShader(_vertex_shader);
            glDeleteShader(_fragment_shader);
        }
    }

    Shader::Shader(const std::string &name, const std::string &vertex_src, const std::string &fragment_src) : _name(name)
    {
    }

    Shader::~Shader()
    {
        glDeleteProgram(_id);
    }

    void Shader::bind() const
    {
        glUseProgram(_id);
    }

    void Shader::unbind() const
    {
        glUseProgram(0);
    }

    void Shader::process_shaders(std::string &shader_src)
    {
        std::stringstream file(shader_src);

        enum class ShaderType
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;

        while (getline(file, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else
            {
                ss[(int)type] << line << std::endl;
            }
        }

        _shader_source_code = {
            .vertex_shader = ss[0].str(),
            .fragment_shader = ss[1].str(),
        };
    }

    uint32_t Shader::compile(uint32_t shader_type, std::string &shader_src)
    {
        uint32_t id = glCreateShader(shader_type);
        const char *src = shader_src.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char *message = (char *)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << message << std::endl;
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    void Shader::create_program()
    {
    }

} // namespace Tuna
