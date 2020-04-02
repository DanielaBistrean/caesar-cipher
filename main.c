#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <unistd.h>

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
    printf ("\t-i\tGet the key from stdin to encrypt/decrypt a file\n");
    printf ("\t-h\tDisplay this information\n");
}

int encrypt (const char *key, const char *infile, const char *outfile)
{
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
            return -1;

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
    int opt, v = 0, h = 0, c = 0, d = 0, i = 0;

    char *key = NULL, *infile, *outfile;

    while((opt = getopt (argc, argv, ":vhc:d:k:i")) != -1) 
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
                break;
            }
            case 'i':
            {
                i = 1;
                break;
            }
            case ':':
            {
                fprintf (stderr, "option needs a value\n");
                exit (1);
                break;
            }
            //case '?':
            default:
            {
                fprintf (stderr, "Unknown option: %c\n", optopt);
                exit (1);
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

    if (i)
    {
        if (key)
        {
            fprintf (stderr, "Ignoring -k argument and waiting for key from stdin\n");
        }
        key = getpass ("");
    }

    if (c && d)
    {
        fprintf (stderr, "You must select one of {c, d}, but not both\n");
        printf ("\n");
        help_content (argv[0]);
        return -1;
    }
    else if (c > 1 || d > 1)
    {
        fprintf (stderr, "You must select {c, d} only once\n");
        printf ("\n");
        help_content (argv[0]);
        return -1;
    }
    else if (c == 0 && d == 0)
    {
        fprintf (stderr, "You must select at least one of {c, d}\n");
        printf ("\n");
        help_content (argv[0]);
        return -1;
    }

    if (key == NULL)
    {
        fprintf (stderr, "You must select a key\n");
        printf ("\n");
        help_content (argv[0]);
        return -1;
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
        return encrypt (key, infile, outfile);
    }
    else
    {
        return decrypt (key, infile, outfile);
    }
}

