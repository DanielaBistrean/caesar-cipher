#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

void version_content ()
{
    printf ("caesar-cipher version: 1.0.20200401\n");
    printf ("Copyright (c) 2020 Daniela-Marinela Bistrean\n");
    printf ("This is free software; see the source for copying conditions.\n");
}

void help_content (const char *program_name)
{
    printf ("Usage:\n");
    printf ("\t%s [OPTION...]\n", program_name);
    printf ("Options:\n");
    printf ("\t-v\tShow the caesar-cipher version\n");
    printf ("\t-c\tEncrypt a file\n");
    printf ("\t-d\tDecript a file\n");
    printf ("\t-k\tSpecify the key for encrypt/decrypt\n");
    printf ("\t-h\tDisplay this information\n");
}

int encrypt (const char *key, const char *infile, const char *outfile)
{
    printf ("Will encrypt \"%s\" with key \"%s\" and save the result to \"%s\"\n", infile, key, outfile);

    int ch, idx = 0;
    FILE *in = fopen (infile, "rb");
    if (in == NULL)
    {
        perror ("Could not open input file");
        return -1;
    }
    
    FILE *out = fopen (outfile, "wb");
    if (out == NULL)
    {
        perror ("Could not open output file");
        fclose (in);
        return -1;
    }

    int key_size = strlen (key);

    do
    {
        ch = fgetc (in);

        if (feof (in))
            break;

        ch = (ch + key[idx]) % 256;
        idx = (idx + 1) % key_size;

        fputc (ch, out);
    } while (1);

    fclose (out);
    fclose (in);
    return 0;
}

int decrypt (const char* key, const char *infile, const char *outfile)
{
    printf ("Will decrypt \"%s\" with key \"%s\" and save the result to \"%s\"\n", infile, key, outfile);

    FILE *in = fopen (infile,"rb");
    if (in == NULL)
    {
        perror ("Could not open input file");
        return -1;
    }

    FILE *out = fopen (outfile, "wb");
    if (out == NULL)
    {
        perror ("Could not open output file");
        fclose (in);
        return -1;
    }

    int ch, idx = 0, key_size = strlen (key);

    do
    {
        ch = fgetc (in);

        if (feof (in))
            return 1;

        ch = (ch - key[idx]) % 256;
        idx = (idx + 1) % key_size;

        fputc (ch, out);
    } while (1);

    fclose (out);
    fclose (in);
    return 0;
}

int main (int argc, char *argv[])
{
    int opt, v = 0, h = 0, c = 0, d = 0;

    char *key = NULL, *infile, *outfile;

    while((opt = getopt (argc, argv, ":vhc:d:k:")) != -1) 
    {
        switch (opt)
        {
            case 'v':
            {
                v = 1;
                break;
            }
            case 'h':
            {
                h = 1;
                break;
            }
            case 'k':
            {
                key = optarg;
                break;
            }
            case 'c':
            {
                c++;
                infile = optarg;
                break;
            }
            case 'd':
            {
                d++;
                infile = optarg;
            }
            case ':':
            {
                printf ("option needs a value\n");
                break;
            }
            case '?':
            {
                printf ("Unknown option: %c\n", optopt);
                break;
            }
        }
    }

    if (h)
    {
        help_content (argv[0]);
        return 0;
    }

    if (v)
    {
        version_content ();
        return 0;
    }

    if (c && d)
    {
        fprintf (stderr, "You must select one of {c, d}, but not both\n");
        printf ("\n");
        help_content (argv[0]);
        return 1;
    }
    else if (c > 1 || d > 1)
    {
        fprintf (stderr, "You must select {c, d} only once\n");
        printf ("\n");
        help_content (argv[0]);
        return 1;
    }
    else if (c == 0 && d == 0)
    {
        fprintf (stderr, "You must select at least one of {c, d}\n");
        printf ("\n");
        help_content (argv[0]);
        return 1;
    }

    if (key == NULL)
    {
        fprintf (stderr, "You must select a key\n");
        printf ("\n");
        help_content (argv[0]);
        return 1;
    }

    if (optind < argc)
    {
        outfile = argv[optind];
    }
    else
    {
        outfile = "out.txt";
    }

    if (c)
    {
        encrypt (key, infile, outfile);
    }
    else
    {
        decrypt (key, infile, outfile);
    }
        
    return 0;
}

