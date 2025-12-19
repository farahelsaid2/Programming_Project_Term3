void strtolower(char *s)
{
    for(int i = 0; s[i]; i++)
        s[i] = tolower((unsigned char)s[i]);
}


// trim leading/trailing spaces and newline
void trim(char *s)
{
    // remove trailing newline/space
    int len = strlen(s);
    while(len > 0 && (s[len-1]==' ' || s[len-1]=='\n' || s[len-1]=='\r'))
        s[--len] = '\0';

    // remove leading spaces
    int start = 0;
    while(s[start] == ' ') start++;
    if(start > 0)
        memmove(s, s + start, len - start + 1); // +1 for '\0'
}