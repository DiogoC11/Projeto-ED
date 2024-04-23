cmake_minimum_required(VERSION 3.27)
project(Exem_Projeto C)

set(CMAKE_C_STANDARD 11)

add_executable(Exem_Projeto main.c
        src/Biblioteca.c
        src/Hashing.c
        src/Lista.c
        src/Livro.c
        src/Pessoa.c
        src/Requisicao.c
        src/Uteis.c
        src/Livro.h
        src/Livro.h)
