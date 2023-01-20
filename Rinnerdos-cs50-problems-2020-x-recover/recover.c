#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        typedef uint8_t BYTE;
    
        FILE *f = fopen(argv[1], "r");
        
        BYTE *buffer = malloc(512 * sizeof(BYTE));
        
        FILE *img = NULL;
        
        int jpegCount = 0; 
        
        char filename[8];
        
        while (fread(buffer, sizeof(BYTE), 512, f) == 512)
        {
            printf("buff[0] is: %i\n", buffer[0]);
            
            // Check for start of new JPEG
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
            {
                if (jpegCount == 0)
                {
                    sprintf(filename, "%03i.jpg", jpegCount);
                        
                    img = fopen(filename, "w");
                
                    fwrite(buffer, sizeof(BYTE), 512, img);
                    
                    jpegCount++;
                }
                else // If new jpeg, close the old one, start new
                {
                    fclose(img);
                    
                    sprintf(filename, "%03i.jpg", jpegCount);
                    
                    img = fopen(filename, "w");
                
                    fwrite(buffer, sizeof(BYTE), 512, img);
                    
                    jpegCount++;
                    
                }
                
            }
            else // -> If not start of new JPEG, keep writing.
            {
                if (jpegCount > 0)
                {
                    fwrite(buffer, sizeof(BYTE), 512, img);
                }
            }
        }
        
        free(buffer);
        
        fclose(img);
        
        return 0;
    }
    else
    {
        return 1;
    }
    
    
}
