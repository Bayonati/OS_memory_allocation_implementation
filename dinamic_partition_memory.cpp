#include <bits/stdc++.h>
using namespace std;

bool text = true;

class Block {
public:
    string tag;
    int size;
    bool free;

    Block(string tag, int size, bool free) : tag(tag), size(size), free(free) {}
};

// Asignación dinámica
void assign(vector<Block> &memory, string p, int size, int policy)
{
    int chosenIdx = -1;

    switch (policy)
    {
    case 1: // First Fit
    {
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i].free && memory[i].size >= size)
            {
                chosenIdx = i;
                break;
            }
        }
        break;
    }

    case 2: // Best Fit
    {
        int bestWastage = INT_MAX;
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i].free && memory[i].size >= size)
            {
                int waste = memory[i].size - size;
                if (waste < bestWastage)
                {
                    bestWastage = waste;
                    chosenIdx = i;
                }
            }
        }
        break;
    }

    case 3: // Worst Fit
    {
        int worstWastage = -1;
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i].free && memory[i].size >= size)
            {
                int waste = memory[i].size - size;
                if (waste > worstWastage)
                {
                    worstWastage = waste;
                    chosenIdx = i;
                }
            }
        }
        break;
    }
    }

    if (chosenIdx == -1)
    {
        if (text) cout << p << " must wait" << endl;
        return;
    }

    // Divide the block if there’s leftover space
    int remaining = memory[chosenIdx].size - size;
    memory[chosenIdx].free = false;
    memory[chosenIdx].tag = p;
    memory[chosenIdx].size = size;

    if (remaining > 0)
        memory.push_back({"Libre", remaining, true});
}

// ============ LIBERAR MEMORIA ============
void freeBlock(vector<Block> &memory, string &tag)
{
    bool found = false;
    for (int i = 0; i < memory.size(); i++)
    {
        if (!memory[i].free && memory[i].tag == tag)
        {
            memory[i].free = true;
            memory[i].tag = "Libre";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Error: Process " << tag << " not found or already free.\n";
}

// ============ MOSTRAR MEMORIA ============
void show(vector<Block> &memory)
{
    for (const auto &b : memory)
    {
        string label = b.free ? "Libre" : b.tag;
        cout << "[" << label << ":" << b.size << "]";
    }
    cout << "\n";
}

// ============ MAIN ============
int main()
{
    int policy = 1; // 1=First Fit, 2=Best Fit, 3=Worst Fit
    vector<Block> memory = {{"Libre", 100, true}}; // memoria total dinámica


    char comand;
    while (cin >> comand)
    {
        switch (comand)
        {
        case 'A': // Asignar
        {
            string p;
            int t;
            cin >> p >> t;
            assign(memory, p, t, policy);
            break;
        }
        case 'L': // Liberar
        {
            string p;
            cin >> p;
            freeBlock(memory, p);
            break;
        }
        case 'M': // Mostrar
        {
            show(memory);
            break;
        }
        case 'P': // Política de asignación
        {
            int p;
            cin >> p;
            policy = p;
            if (p == 1) cout << "First Fit:\n";
            else if (p == 2) cout << "Best Fit:\n";
            else if (p == 3) cout << "Worst Fit:\n";
            else cout << "Error: not an option\n";
            break;
        }
        default:
            cout << "Error: Command " << comand << " not defined\n";
        }
    }

    return 0;
}
