#include <bits/stdc++.h>
using namespace std;

bool text = true;

class Block{
public:
    string tag;
    int memory, ogMemory;
    bool free;

    Block(string tag, int memory, bool free) : tag(tag), memory(memory), ogMemory(memory), free(free) {}
};

void assign(vector<Block> &memory, string p, int size, int policy)
{
    switch (policy)
    {
    case 1: // First Fit Allocation
    {
        bool ok = false;
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i].free && size <= memory[i].memory)
            {
                ok = true;
                if (text) cout << p << " is put in " << memory[i].memory << " partion" << endl;;

                memory[i].memory -= size;
                memory[i].free = false;
                memory[i].tag = p;
                break; // Stop at first fit
                // cout << "  " << p << " (" << size << "KB) is put in " << memory[i].memory << "KB partition\n";
            }
        }
        if (!ok){
            //cout << "Error: Couldn't fit " << p << "\n";
            if (text) cout << p << " must wait" << endl;
        }
        break;
    }

    case 2: // Best Fit Allocation
    {
        int bestIdx = -1;
        int minWastage = INT_MAX;
        // Find the smallest block that can fit the process
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i].free && size <= memory[i].memory)
            {
                int wastage = memory[i].memory - size;
                if (wastage < minWastage)
                {
                    minWastage = wastage;
                    bestIdx = i;
                }
            }
        }

        if (bestIdx != -1)
        {
            if (text) cout << p << " is put in " << memory[bestIdx].memory << " partion" <<endl;
            memory[bestIdx].memory -= size;
            memory[bestIdx].free = false;
            memory[bestIdx].tag = p;
        }
        else
        {
            //cout << "Error: Couldn't fit " << p << "\n";
            if (text) cout << p << " must wait" << endl;
        }
        break;
    }

    case 3: // Worst Fit Allocation
    {
        int worstIdx = -1;
        int maxWastage = -1;

        // Find the largest block that can fit the process
        for (int i = 0; i < memory.size(); i++)
        {
            if (memory[i].free && size <= memory[i].memory)
            {
                int wastage = memory[i].memory - size;
                if (wastage > maxWastage)
                {
                    maxWastage = wastage;
                    worstIdx = i;
                }
            }
        }

        if (worstIdx != -1)
        {
            if (text) cout << p << " is put in " << memory[worstIdx].memory << " partion" << endl;
            memory[worstIdx].memory -= size;
            memory[worstIdx].free = false;
            memory[worstIdx].tag = p;
        }
        else
        {
            //cout << "Error: Couldn't fit " << p << "\n";
            if (text) cout << p << " must wait" << endl;
        }
        break;
    }
    }
}

void free(vector<Block> &memory, string &tag)
{
    bool found = false;
    for (int i = 0; i < memory.size(); i++)
    {
        if (!memory[i].free && memory[i].tag == tag)
        {
            found = true;
            memory[i].free = true;
            memory[i].tag = "B" + to_string(i + 1); // Reset tag
            memory[i].memory = memory[i].ogMemory;
            break;
        }
    }
    if (!found)
    {
        cout << "Error: Process " << tag << " not found or is already free.\n";
    }
}

void show(vector<Block> &memory)
{
    for (const auto &block : memory)
    {
        string label = block.free ? "Libre" : block.tag;
        cout << "[" << label << ":" << block.memory << "]";
    }
    cout << "\n";
}

int main()
{
    int policy = 1;
    // 1: First Fit Allocation, 2: Best Fit Allocation, 3: Worst Fit Allocation

    // Podemos también fácilmente agregar un menu que pida por input la memoria
    vector<Block> memory0;
    memory0.push_back({"B1", 20, true});
    memory0.push_back({"B2", 100, true});
    memory0.push_back({"B3", 40, true});
    memory0.push_back({"B4", 200, true});
    memory0.push_back({"B5", 10, true});

    vector<Block> memory1;
    memory1.push_back({"B1", 100, true});
    memory1.push_back({"B2", 50, true});
    memory1.push_back({"B3", 30, true});
    memory1.push_back({"B4", 120, true});
    memory1.push_back({"B5", 35, true});

    vector<Block> memory2;
    memory2.push_back({"B1", 20, true});
    memory2.push_back({"B2", 100, false});
    memory2.push_back({"B3", 40, true});
    memory2.push_back({"B4", 200, false});
    memory2.push_back({"B5", 10, true});

    vector<Block> memory3 = {
        {"B1", 100, true},
        {"B2", 500, true},
        {"B3", 200, true},
        {"B4", 300, true},
        {"B5", 600, true}
    };

    vector<Block> memory = memory3;

    char comand;
    while (cin >> comand)
    {
        switch (comand)
        {
        case 'A':
        {
            string p; int t; cin >> p >> t;
            assign(memory, p, t, policy);
            break;
        }
        case 'L':
        {
            string p; cin >> p;
            free(memory, p);
            break;
        }
        case 'M':
        {
            show(memory);
            break;
        }
        case 'P': //Comando para escoger la política disponible
        {
            int p; cin >> p;
            policy = p;
            if (p == 1) cout << "First-fit:" << endl;
            if (p == 2) cout << "Best-fit:" << endl;
            if (p == 3) cout << "Worst-fit:" << endl;
            if (p < 1 || p > 3) cout << "Error: not an option" << endl;
            break;
        }
        case 'C': //Comando para escoger una memoria disponible
        {
            int c; cin >> c;
            if (c == 0) memory = memory0;
            if (c == 1) memory = memory1;
            if (c == 2) memory = memory2;
            if (c == 3)  memory = memory3;
            if (c < 0 || c > 3) cout << "Error: not an option" << endl;
            break;
        }

        default:
            cout << "Error: Command: " << comand << " not defined" << endl;
        }
    }
    return 0;
}