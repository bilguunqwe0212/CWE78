

#include <wchar.h>

#ifdef _WIN32
#define FULL_COMMAND "%WINDIR%\\system32\\cmd.exe /c dir "
#else
#include <unistd.h>
#define FULL_COMMAND "/bin/sh ls -la "
#endif

namespace GenNS1
{

class GenClass1
{
public:
    virtual void action(char * data) = 0;
};



class GenClass2 : public GenClass1
{
public:
    void action(char * data);
};

}



#ifdef _WIN32
#define POPEN _popen
#define PCLOSE _pclose
#else 
#define POPEN popen
#define PCLOSE pclose
#endif

namespace GenNS1
{

void GenClass2::action(char * data)
{
    {
        FILE *pipe;
        pipe = POPEN(data, "wb");
        if (pipe != NULL)
        {
            PCLOSE(pipe);
        }
    }
}

}


namespace GenNS1
{



void func2()
{
    char * data;
    char data_buf[100] = FULL_COMMAND;
    data = data_buf;
    {
        size_t dataLen = strlen(data);
        if (100-dataLen > 1)
        {
            if (fgets(data+dataLen, (int)(100-dataLen), stdin) != NULL)
            {
                dataLen = strlen(data);
                if (dataLen > 0 && data[dataLen-1] == '\n')
                {
                    data[dataLen-1] = '\0';
                }
            }
            else
            {
                printLine("fgets() failed");
                data[dataLen] = '\0';
            }
        }
    }
    GenClass1* baseObject = new GenClass2;
    baseObject->action(data);
    delete baseObject;
}

} 



using namespace GenNS1; 

int main(int argc, char * argv[])
{
    srand( (unsigned)time(NULL) );

    printLine("Calling ...");
    func2();
    printLine("Finished");
    return 0;
}
