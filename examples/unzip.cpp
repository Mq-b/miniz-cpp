#include "../zip_file.hpp"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

// 函数：解压 ZIP 文件到指定的输出目录
bool extract_zip(const std::string& zip_path, const std::string& output_dir)
{
    try
    {
        // 打开 ZIP 文件
        miniz_cpp::zip_file file{ zip_path };

        // 确保输出目录存在
        fs::create_directories(output_dir);

        // 遍历 ZIP 文件包中的所有文件
        for (const auto& zip_info : file.infolist())
        {
            std::string output_file_path = output_dir + "/" + zip_info.filename;

            if (zip_info.filename.back() == '/')
            {
                // 如果目录项是文件夹，则创建目录
                fs::create_directories(output_file_path);
            }
            else
            {
                // 确保父目录存在
                fs::create_directories(fs::path(output_file_path).parent_path());

                // 解压文件内容并写入目标文件
                std::ofstream output_file(output_file_path, std::ios::binary);
                if (!output_file)
                {
                    std::cerr << "创建文件失败：" << output_file_path << std::endl;
                    return false;
                }
                // 从 zip 中读取对应文件并写入到输出文件
                output_file << file.read(zip_info.filename);
            }
        }

        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "解压 ZIP 文件时发生错误：" << e.what() << std::endl;
        return false;
    }
}

int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
        std::cout << "usage: " << argv[0] << " filename output" << std::endl;
        return 0;
    }

    std::string zip_path = argv[1];
    std::string output_dir = argv[2];

    if (extract_zip(zip_path, output_dir))
    {
        std::cout << "Extraction completed successfully to " << output_dir << std::endl;
    }
    else
    {
        std::cerr << "Extraction failed." << std::endl;
    }
}
