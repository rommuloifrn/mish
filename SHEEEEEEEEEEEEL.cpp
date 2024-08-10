#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

#include <bits/stdc++.h>
using namespace std;

string mish_command(string input) {
    stringstream ss(input);
    string word; vector<string> vec;
    ss >> word;

    return word;
}

vector<string> mish_args(string input) {
    stringstream ss(input);
    string word; vector<string> vec;

    while (ss >> word)
        vec.push_back(word);

    vec.erase(vec.begin());
    return vec;
}

void execute(string path, string command) {
    pid_t pid = fork();
    if (pid < 0){ // Erro
        std::cout << "Erro de execução!" << std::endl;
        return;
    } else if (pid == 0){ //processo filho
        char * argv[2] = {(char *)command.c_str(), nullptr};
        execve(path.c_str(), argv, NULL);
    } else { // Processo pai
        /* Deve adicionar processo filho na lista (std::vector)
        de processos em execução para gerenciar background. */
        /* Processo pai espera processo filho terminar. */
        waitpid(pid, nullptr, 0);
    }
}

void try_executing(string command, vector<string>& args) {
    if ( (!args.empty()) && (args.back() == "&") ) // trata background
            cout << "background não tratado!\n";


    std::string absolute_path = "/bin/" + command;

    if (access(absolute_path.c_str(), F_OK) == 0) { // Arquivo existe no diretório
        if (access(absolute_path.c_str(), X_OK) == 0) { // Arquivo é executável
            execute(absolute_path, command);
        } else { // Arquivo não é executável
            std::cout << "permission denied1: " << command << std::endl;
        }
    } else if (access(command.c_str(), F_OK) == 0) {
        if (access(command.c_str(), X_OK) == 0) { // Arquivo é executável
            execute("", command);
        } else { // Arquivo não é executável
            std::cout << "permission denied: " << command << std::endl;
        }
    }
    else { // Arquivo não existe
        std::cout << "Command not found: " << command << std::endl;
    }
}

void process_command(std::string input) {

    string command = mish_command(input);
    vector<string> args = mish_args(input);
    
    // Se for comando interno...
    if (command == "exit")
        exit(0);
    else if (command == "pwd")
        cout << "pwd não implementado!\n";
    else if (command == "cd")
        cout << "cd não implementado!\n";
    else if (command == "history")
        cout << "history não implementado!\n";
    else {
        // Se for comando externo

        // * necessário verificar se é para ser executado em background
        /*  Se for caminho relativo, procurar o comando na lista de diretórios
            Se for absoluto verifica se comando existe
        */

        // tratamento de comando em background
        try_executing(command, args);
        
    }
    

    
}

int main() {
    while (true) {
        std::cout << "$ "; // printa o prompt "$"
        std::string command;
        getline(std::cin, command);
        process_command(command);
    }
    return 0;
}
