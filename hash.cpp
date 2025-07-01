#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>
#include <algorithm> 
#include <cctype> 
using namespace std;

struct Movie {
    string title;
    int year;
    float rating;
    string genre;

    Movie() {}
    Movie(string t, int y, float r, string g) : title(t), year(y), rating(r), genre(g) {}
};

// AVLNode - Codigo de Sala
class AVLNode 
{
public:
    Movie movie;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const Movie& m) : movie(m), left(nullptr), right(nullptr), height(1) {}

    int getHeight(AVLNode* node) {return node ? node->height : 0;}

    int getBalance() {return getHeight(left) - getHeight(right);}

    void updateHeight() {height = 1 + max(getHeight(left), getHeight(right));}

    AVLNode* rotateRight() 
    {
        AVLNode* x = left;
        AVLNode* T2 = x->right;

        x->right = this;
        this->left = T2;

        this->updateHeight();
        x->updateHeight();

        return x;
    }

    AVLNode* rotateLeft() 
    {
        AVLNode* y = right;
        AVLNode* T2 = y->left;

        y->left = this;
        this->right = T2;

        this->updateHeight();
        y->updateHeight();

        return y;
    }

    AVLNode* insert(const Movie& m) 
    {
        if (m.rating > movie.rating) 
        {
            if (left) {left = left->insert(m);}
            else {left = new AVLNode(m);}
        } 
        else 
        { 
            if (right) {right = right->insert(m);}
            else {right = new AVLNode(m);}
        }

        updateHeight();
        int balance = getBalance();

        // LL
        if (balance > 1 && m.rating > left->movie.rating) {return rotateRight();}
        // RR
        if (balance < -1 && m.rating <= right->movie.rating) {return rotateLeft();}
        // LR
        if (balance > 1 && m.rating <= left->movie.rating) 
        {
            left = left->rotateLeft();
            return rotateRight();
        }
        // RL
        if (balance < -1 && m.rating > right->movie.rating) 
        {
            right = right->rotateRight();
            return rotateLeft();
        }

        return this;
    }

    void inorder() 
    {
        if (left) {left->inorder();}
        cout << "[" << movie.year << "] " << movie.title << " (Nota: " << movie.rating << ")\n";
        if (right) {right->inorder();}
    }

    void searchByTitle(const string& searchTitle, bool& found) 
    {
        if (left) { left->searchByTitle(searchTitle, found);}

        string nodeTitle = movie.title;
        transform(nodeTitle.begin(), nodeTitle.end(), nodeTitle.begin(), ::tolower);
        string searchLower = searchTitle;
        transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        if (nodeTitle.find(searchLower) != string::npos) 
        {
            cout << "Título: " << movie.title << endl;
            cout << "Ano: " << movie.year << endl;
            cout << "Nota: " << movie.rating << endl;
            cout << "Gênero: " << movie.genre << endl;
            cout << "---------------------" << endl;
            found = true;
        }

        if (right){right->searchByTitle(searchTitle, found);}
    }

    int countNodes() 
    {
        int leftCount = left ? left->countNodes() : 0;
        int rightCount = right ? right->countNodes() : 0;
        return 1 + leftCount + rightCount;
    }

    void clear() 
    {
        if (left) 
        {
            left->clear();
            delete left;
            left = nullptr;
        }
        if (right) 
        {
            right->clear();
            delete right;
            right = nullptr;
        }
    }
};

// LinkedList - ED1 Adaptado
struct ListNode 
{
    string genre;
    AVLNode* root;
    ListNode* next;

    ListNode(const string& g) : genre(g), root(nullptr), next(nullptr) {}
};


//  Hash -> LinkedList -> AVLTree
class HashTable 
{
    static const int TABLE_SIZE = 1009;
    ListNode* table[TABLE_SIZE];

    int hashFunction(const string& key) 
    {
        int hash = 0;
        for (char c : key) 
        {
            hash = (hash * 31 + c) % TABLE_SIZE;
        }
        return hash;
    }

    ListNode* findGenreNode(int i, const string& genre) 
    {
        ListNode* curr = table[i];
        while (curr) 
        {
            if (curr->genre == genre) {return curr;}
            curr = curr->next;
        }
        return nullptr;
    }

    int countAVLNodes(AVLNode* node) 
    {
        if (!node) {return 0;}
        return 1 + countAVLNodes(node->left) + countAVLNodes(node->right);
    }

    void searchInAVL(AVLNode* node, const string& title, bool& found) 
    {
        if (!node) return;
        
        searchInAVL(node->left, title, found);
        
        string nodeTitle = node->movie.title;
        transform(nodeTitle.begin(), nodeTitle.end(), nodeTitle.begin(), ::tolower);
        string searchTitle = title;
        transform(searchTitle.begin(), searchTitle.end(), searchTitle.begin(), ::tolower);
        
        if (nodeTitle.find(searchTitle) != string::npos) {
            cout << "Título: " << node->movie.title << endl;
            cout << "Ano: " << node->movie.year << endl;
            cout << "Nota: " << node->movie.rating << endl;
            cout << "Gênero: " << node->movie.genre << endl;
            cout << "---------------------" << endl;
            found = true;
        }
        
        searchInAVL(node->right, title, found);
    }

    void deleteAVLTree(AVLNode* node) 
    {
        if (!node) return;
        deleteAVLTree(node->left);
        deleteAVLTree(node->right);
        delete node;
    }

    public:
        HashTable() 
        {
            for (int i = 0; i < TABLE_SIZE; i++) {table[i] = nullptr;}
        }

        void insert(const Movie& movie) 
        {
            int idx = hashFunction(movie.genre);
            ListNode* genreNode = findGenreNode(idx, movie.genre);

            if (!genreNode) {
                genreNode = new ListNode(movie.genre);
                genreNode->next = table[idx];
                table[idx] = genreNode;
            }

            if (genreNode->root) {genreNode->root = genreNode->root->insert(movie);}
            else { genreNode->root = new AVLNode(movie); }

        }

        void printByGenre(const string& genre) {
            int idx = hashFunction(genre);
            ListNode* genreNode = findGenreNode(idx, genre);

            if (!genreNode || !genreNode->root) {
                cout << "Nenhum filme encontrado para o gênero: " << genre << endl;
                return;
            }

            cout << "Filmes do gênero \"" << genre << "\":\n";
            if (genreNode->root) {genreNode->root->inorder();} 
        }

        int countAllMovies() {
            int total = 0;
            for (int i = 0; i < TABLE_SIZE; i++) {
                ListNode* curr = table[i];
                while (curr) {
                    total += countAVLNodes(curr->root);
                    curr = curr->next;
                }
            }
            return total;
        }

        int countByGenre(const string& genre) {
            int idx = hashFunction(genre);
            ListNode* genreNode = findGenreNode(idx, genre);
            if (!genreNode) return 0;
            
            // Implementar uma função para contar nós na AVL
            return countAVLNodes(genreNode->root);
        }

        void searchByTitle(const string& title) {
            bool found = false;
            for (int i = 0; i < TABLE_SIZE; i++) {
                ListNode* curr = table[i];
                while (curr) {
                    if (curr->root) {curr->root->searchByTitle(title, found);}
                    curr = curr->next;
                }
            }
            
            if (!found) {
                cout << "Nenhum filme encontrado com o título \"" << title << "\"" << endl;
            }
        }

        void deleteByGenre(const string& genre) {
            int idx = hashFunction(genre);
            ListNode* curr = table[idx];
            ListNode* prev = nullptr;

            while (curr) {
                if (curr->genre == genre) {
                    // Deleta a árvore AVL completa
                    deleteAVLTree(curr->root);
                    curr->root = nullptr;

                    // Remove o nó da lista encadeada
                    if (prev) {
                        prev->next = curr->next;
                    } else {
                        table[idx] = curr->next;
                    }

                    ListNode* toDelete = curr;
                    curr = curr->next;
                    delete toDelete;

                    cout << "Todos os filmes do gênero \"" << genre << "\" foram removidos." << endl;
                    return;
                }
                prev = curr;
                curr = curr->next;
            }

            cout << "Gênero \"" << genre << "\" não encontrado." << endl;
        }
};

// Função que lê o arquivo
vector<Movie> loadFile(const string& filename) {
    vector<Movie> movies;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Erro ao abrir o arquivo: " << filename << endl;
        return movies;
    }

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        size_t pos3 = line.find(';', pos2 + 1);

        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
            continue;

        string title = line.substr(0, pos1);
        int year = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        float rating = stof(line.substr(pos2 + 1, pos3 - pos2 - 1));
        string genre = line.substr(pos3 + 1);

        movies.emplace_back(title, year, rating, genre);
    }
    file.close();
    return movies;
}

int generateMovies()
{
    int result = system("python movie.py || python3 movie.py");
    return result;
}
int main() {
    
    HashTable ht;

    while(true)
    {
        int option = 0;
        string word;
        system("clear");
        cout << "=== SISTEMA DE GERENCIAMENTO DE FILMES POR GENERO ===\n\n";
        cout << "Total de filmes carregados: " << ht.countAllMovies() << "\n";
        cout << "=========================================================\n";
        cout << "Filmes do gênero Ação: " << ht.countByGenre("Ação") << "\n";
        cout << "Filmes do gênero Comédia: " << ht.countByGenre("Comédia") << "\n";
        cout << "Filmes do gênero Romance: " << ht.countByGenre("Romance") << "\n";
        cout << "Filmes do gênero Drama: " << ht.countByGenre("Drama") << "\n";
        cout << "Filmes do gênero Ficção Científica: " << ht.countByGenre("Ficção Científica") << "\n";
        cout << "Filmes do gênero Terror: " << ht.countByGenre("Terror") << "\n";
        cout << "Filmes do gênero Suspense: " << ht.countByGenre("Suspense") << "\n";
        cout << "Filmes do gênero Fantasia: " << ht.countByGenre("Fantasia") << "\n\n";
        cout << "Opções:\n";
        cout << "1 - Busca de Filmes por Gênero\n";
        cout << "2 - Busca de Filme por Título\n";
        cout << "3 - Deletar Filmes por Gênero\n";
        cout << "100 - Exportar Filmes de arquivo\n";
        cout << "101 - Inserir Filme por Input\n";
        cout << "0 - Sair\n";
        cout << "=========================================================\n";
        cout << "Opção\n";
        cin >> option;

        if (option == 0)
        {
            break;
        }
        

        if (option == 1)
        {
            system("clear");
            cout << "=== BUSCAR FILMES ===" << endl;
            cout << "Digite o Gênero que deseja Consultar: ";
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //limpa o buffer até EOF - O(n);
            getline(cin, word); // Percorre até EOF - armazena na variavel O(n);

            ht.printByGenre(word);

            cout << "\nPressione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (option == 2)
        {
            system("clear");
            cout << "=== PESQUISAR FILME POR TÍTULO ===" << endl;
            cout << "Digite parte do título que deseja buscar: ";
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, word);
            
            ht.searchByTitle(word);
            
            cout << "\nPressione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (option == 3)
        {
            system("clear");
            cout << "=== DELETAR FILMES POR GÊNERO ===" << endl;
            cout << "Digite o gênero que deseja deletar: ";
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, word);
            
            ht.deleteByGenre(word);
            
            cout << "\nPressione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (option == 100)
        {
            int result = generateMovies();
            if(result != 1)
            {
                cout << "Gerado Com sucesso";
            } else {
                cout << "Algo Deu Ruim";
            }

            string filename = "movies.txt";
            vector<Movie> movies = loadFile(filename);
            if (movies.empty()) {
                cout << "Nenhum filme\n";
            } else {
                for (const Movie& m : movies) {
                    ht.insert(m);
                }
                cout << "Filmes carregados com sucesso!\n";
            }
            cout << "Pressione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (option == 101)
        {
            system("clear");
            cout << "=== INSERIR NOVO FILME ===" << endl;
            
            Movie novoFilme;
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            cout << "Título: ";
            getline(cin, novoFilme.title);
            
            cout << "Ano: ";
            while (!(cin >> novoFilme.year)) {
                cout << "Por favor, digite um ano válido: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            cout << "Nota (0.0-10.0): ";
            while (!(cin >> novoFilme.rating) || novoFilme.rating < 0 || novoFilme.rating > 10) {
                cout << "Por favor, digite uma nota válida (0.0 a 10.0): ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Gênero: ";
            getline(cin, novoFilme.genre);
            
            ht.insert(novoFilme);
            
            cout << "\nFilme inserido com sucesso!\n";
            cout << "Pressione Enter para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
    }

    return 0;
}