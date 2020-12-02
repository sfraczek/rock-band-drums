#include <fstream>

struct TemporaryFile
{
    TemporaryFile();
    ~TemporaryFile();

    void Write(const char *data)
    {
        fs.open(fname);
        fs << data;
        fs.close();
    }

    std::string Name() const
    {
        return fname;
    }

private:
    std::string fname;
    std::ofstream fs;
};