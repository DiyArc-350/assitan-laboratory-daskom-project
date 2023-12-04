if (listing.id == id && strcasecmp(listing.request, "pending") != 0 && strcasecmp(key, "menuBeli") == 0 || strcasecmp(key, "menuSewa") == 0)
        {
            printf("%d.  ID\t\t: %d\n", x + 1, listing.id);
            printf("    Jenis\t: %s\n", listing.jenis);
            printf("    Merk\t: %s\n", listing.merk);
            printf("    Nama\t: %s\n", listing.nama);
            printf("    Pemilik\t: %s\n", listing.username);
            printf("    Status\t: ");
            if (strcasecmp(listing.status, "jual") == 0)
            {
                green(listing.status);
                reset();
                printf("\n    Harga\t: Rp.%.2f\n\n", listing.harga);
            }
            else if (strcasecmp(listing.status, "sewa") == 0)
            {
                cyan(listing.status);
                reset();
                printf("\n    Harga Sewa\t: Rp.%.2f\n\n", listing.hargaSewa);
            }
            x++;
            break;
        }