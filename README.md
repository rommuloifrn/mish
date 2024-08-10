# mish

![](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

Minimal shell implementation written in C++ for a college project.

## Documentação

A mish roda programas armazenados no /bin/ e tenta acessar programas no diretório local, mas isso não acontece devido a um erro na fragmentação das funções.

comandos internos:

- exit - sai da mish
- pwd/cd/history retornam um aviso de não-implementação

comandos externos:

A mish fragmenta o input do usuário, separando a primeira palavra (considerada o comando) e o resto (considerados os argumentos). Os argumentos não são tratados, apesar de a verificação do símbolo para rodar em background não existir.