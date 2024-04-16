cmake_minimum_required(VERSION 3.27)
project(Exem_Projeto C)

set(CMAKE_C_STANDARD 11)

add_executable(Exem_Projeto main.c
        Biblioteca.c
        Hashing.c
        Lista.c
        Livro.c
        Pessoa.c
        Requisicao.c
        Uteis.c)
