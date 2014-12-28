#include <stdio.h>
#include <unistd.h>
#include <openssl/md5.h>
using namespace std;

int main()
{
    int i;
    MD5_CTX md5handler;
    unsigned char md5digest[MD5_DIGEST_LENGHT];
    char recvbuff[4]={1,2,0,20};
    MD5_Init(&md5handler);
    MD5_Update(&md5handler,(const char*)recvbuff[0],1);
    MD5_Final(md5digest,&md5handler);
    for(i=0;i<MD5_DIGEST_LENGTH;i++)
       printf("%02x",md5gigest[i]);
    printf("/n");
}
