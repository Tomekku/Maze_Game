#include "../include/functions.h"

char *realpath(const char *path, char resolved_path[PATH_MAX])
{
  char *return_path = 0;

  if (path)
  {
    if (resolved_path)
    {
      return_path = resolved_path;
    }
    else
    {
      return_path = malloc(PATH_MAX); 
    }

    if (return_path)
    {
      size_t size = GetFullPathNameA(path, PATH_MAX, return_path, 0);

      if (size > PATH_MAX)
      {
        if (return_path != resolved_path)
        {
          size_t new_size;
          
          free(return_path);
          return_path = malloc(size);

          if (return_path)
          {
            new_size = GetFullPathNameA(path, size, return_path, 0);

            if (new_size > size)
            {
              free(return_path);
              return_path = 0;
              errno = ENAMETOOLONG;
            }
            else
            {
              size = new_size;
            }
          }
          else
          {
            errno = EINVAL;
          }  
        }
        else 
        {
          return_path = 0;
          errno = ENAMETOOLONG;
        }
      }

      if (!size) 
      {
        if (return_path != resolved_path)
        {
          free(return_path);
        }
        
        return_path = 0;

        switch (GetLastError())
        {
          case ERROR_FILE_NOT_FOUND:
            errno = ENOENT;
            break;

          case ERROR_PATH_NOT_FOUND: case ERROR_INVALID_DRIVE:
            errno = ENOTDIR;
            break;

          case ERROR_ACCESS_DENIED:
            errno = EACCES;
            break;
          
          default:
            errno = EIO;
            break;
        }
      }

      if (return_path)
      {
        struct stat stat_buffer;

        if (stat(return_path, &stat_buffer)) 
        {
          if (return_path != resolved_path)
          {
            free(return_path);
          }
        
          return_path = 0;
        }
      }
    }
    else
    {
      errno = EINVAL;
    }
  }
  else
  {
    errno = EINVAL;
  }
    
  return return_path;
}
