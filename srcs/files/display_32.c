//
// Created by tnoulens on 9/26/23.
//

#include "ft_nm.h"

char    put_symbol32(const Elf32_Sym *symtab, const Elf32_Shdr *sht)
{
    (void)sht;
    if (symtab->st_info == STT_FILE)
        return ('a');
    else if (symtab->st_info == STB_LOCAL)
    {
        return ('t');
    }
    else if (symtab->st_info == STB_GLOBAL)
    {
        return ('T');
    }
    else if (symtab->st_info == STB_GNU_UNIQUE)
    {
        return ('u');
    }
    return ('?');
}

void printDymSym32(const Elf32_Sym *dynsym, uint32_t dynsym_size, char *dynstr, char *symname, const int opt)
{
    ft_printf ("\n# .dynsym entries:\n");
    for (uint32_t i = 0; i < (dynsym_size / sizeof(Elf32_Sym)); i++)
    {
        if (readWord(dynsym[i].st_value, opt) == 0)
        {
            ft_printf("%s ", NULL_PAD8);
        }
        else
        {
            char    buffer[9] = {0,0,0,0,0,0,0,0,0};
            hex(buffer, 0, readWord(dynsym[i].st_value, opt), B32);
            ft_printf("%s ", buffer);
        }
        symname = &dynstr[readWord(dynsym[i].st_name, opt)];
        if (*symname == '\x00')
            ft_printf("NULL\n");
        else
            ft_printf("%s\n", symname);
    }
}

void    parseSymbols32(t_file *file, uint8_t *map)
{
    int             opt = file->hdr_opt;
    Elf32_Ehdr      *ehdr = (Elf32_Ehdr *)map;
    Elf32_Shdr      *sht = (Elf32_Shdr *)&map[readWord(ehdr->e_shoff, opt)];
    const uint8_t   *shstrtab = &map[readWord(sht[readHalf(ehdr->e_shstrndx, opt)].sh_offset, opt)];
    Elf32_Sym       *symtab = NULL;
    uint32_t        symtab_size = 0;
    char            *symstr = NULL;
    Elf32_Sym       *dynsym = NULL;
    uint32_t        dynsym_size = 0;
    char            *dynstr = NULL;
    char            *value = NULL;
    char            *type = NULL;
    char            *symname = NULL;

    ft_printf("Sections containing symbols:\n");
    for (size_t i = 0; i < readHalf(ehdr->e_shnum, opt); i++)
    {
        const uint8_t *section_name = &shstrtab[readWord(sht[i].sh_name, opt)];
        if (!ft_strncmp(".dynsym", (const char *) section_name, 7)
            && readWord(sht[i].sh_type, opt) == SHT_DYNSYM)
        {
            ft_printf("%s shdr @ 0x%x\n", section_name, readWord(sht[i].sh_offset, opt));
            dynsym = (Elf32_Sym *) &map[readWord(sht[i].sh_offset, opt)];
            dynsym_size = readWord(sht[i].sh_size, opt);
        }
        else if (!ft_strncmp(".dynstr", (const char *) section_name, 7)
                 && readWord(sht[i].sh_type, opt) == SHT_STRTAB)
        {
            ft_printf("%s shdr @ 0x%x\n", section_name, readWord(sht[i].sh_offset, opt));
            dynstr = (char *)&map[readWord(sht[i].sh_offset, opt)];
        }
        else if (!ft_strncmp(".symtab", (const char *) section_name, 7)
                 && readWord(sht[i].sh_type, opt) == SHT_SYMTAB)
        {
            ft_printf("%s shdr @ 0x%x\n", section_name, readWord(sht[i].sh_offset, opt));
            symtab = (Elf32_Sym *)&map[readWord(sht[i].sh_offset, opt)];
            symtab_size = readWord(sht[i].sh_size, opt);
        }
        else if (!ft_strncmp(".strtab", (const char *)section_name, 7)
                 && readWord(sht[i].sh_type, opt) == SHT_STRTAB)
        {
            ft_printf("%s shdr @ 0x%x\n", section_name, readWord(sht[i].sh_offset, opt));
            symstr = (char *)&map[readWord(sht[i].sh_offset, opt)];
        }
        else if ((file->hdr_opt & A)
                 && ft_strnstr((const char *) section_name, "debug", ft_strlen((const char *)section_name)))
        {
            ft_printf("%s shdr @ 0x%x\n", section_name, readWord(sht[i].sh_offset, opt));
        }
        else if ((file->hdr_opt & A)
                 && ft_strnstr((const char *) section_name, "dbg", ft_strlen((const char *)section_name)))
        {
            ft_printf("%s shdr @ 0x%x\n", section_name, readWord(sht[i].sh_offset, opt));
        }
    }
    // TODO: remove printDymSym
    printDymSym32(dynsym, dynsym_size, dynstr, symname, opt);
    ft_printf ("\n# .symtab entries:\n");
    for (uint32_t i = 0; i < (symtab_size / sizeof(Elf32_Sym)); i++)
    {
        if (readWord(symtab[i].st_value, opt) == '\x00')
        {
            value = ft_strdup(NULL_PAD8);
            if (!value)
            {
                file->hdr_opt |= ERROR;
                ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
                return ;
            }
        }
        else
        {
            char    buffer[9] = {0,0,0,0,0,0,0,0,0};
            hex(buffer, 0, symtab[i].st_value, B32);
            value = ft_strdup(buffer);
            if (!value)
            {
                file->hdr_opt |= ERROR;
                ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
                return ;
            }
        }
        type = ft_strdup(" ");
        if (!type)
        {
            file->hdr_opt |= ERROR;
            ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
            return ;
        }
        type[0] = put_symbol32(&symtab[i], sht);
        if (symstr[readWord(symtab[i].st_name, opt)] == '\x00')
            symname = ft_strdup("NULL");
        else
            symname = ft_strdup(&symstr[readWord(symtab[i].st_name, opt)]);
        if (!symname)
        {
            file->hdr_opt |= ERROR;
            ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
            return ;
        }
        add_node_obj(file, value, type, symname);
        if (file->hdr_opt & ERROR)
        {
            ft_fprintf(2, "ft_nm: parseSymbols32: %s", strerror(errno));
            return ;
        }
    }
    if (file->hdr_opt & P)
        displayLstObj(&file->objlst);
    else if (file->hdr_opt & R)
        displayLstObjR(&file->objlst);
    else
        displayLstObjS(&file->objlst);
}
