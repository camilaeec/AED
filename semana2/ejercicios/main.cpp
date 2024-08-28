#include <iostream>

// Nodo de la lista con template
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

// forwardList con template
template <typename T>
class forwardList {
private:
    Node<T>* head;
    int listSize;

    // Funciones auxiliares para merge sort
    Node<T>* merge(Node<T>* left, Node<T>* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->data <= right->data) {
            left->next = merge(left->next, right);
            return left;
        } else {
            right->next = merge(left, right->next);
            return right;
        }
    }

    Node<T>* split(Node<T>* start) {
        Node<T>* slow = start;
        Node<T>* fast = start->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        Node<T>* mid = slow->next;
        slow->next = nullptr;
        return mid;
    }

    Node<T>* mergeSort(Node<T>* start) {
        if (!start || !start->next) return start;

        Node<T>* mid = split(start);
        Node<T>* left = mergeSort(start);
        Node<T>* right = mergeSort(mid);

        return merge(left, right);
    }

public:
    forwardList() : head(nullptr), listSize(0) {}

    ~forwardList() {
        clear();
    }

    T front() const {
        if (!head) throw std::runtime_error("La lista está vacía");
        return head->data;
    }

    T back() const {
        if (!head) throw std::runtime_error("La lista está vacía");

        Node<T>* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp->data;
    }

    void push_front(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        listSize++;
    }

    void push_back(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        listSize++;
    }

    T pop_front() {
        if (!head) throw std::runtime_error("La lista está vacía");

        Node<T>* temp = head;
        T val = temp->data;
        head = head->next;
        delete temp;
        listSize--;
        return val;
    }

    T pop_back() {
        if (!head) throw std::runtime_error("La lista está vacía");

        if (!head->next) {
            T val = head->data;
            delete head;
            head = nullptr;
            listSize--;
            return val;
        }

        Node<T>* temp = head;
        while (temp->next && temp->next->next) {
            temp = temp->next;
        }
        T val = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        listSize--;
        return val;
    }

    T operator[](int index) const {
        if (index < 0 || index >= listSize) throw std::out_of_range("Índice fuera del rango");
        Node<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return listSize;
    }

    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        listSize = 0;
    }

    void sort() {
        if (!head || !head->next) return;
        head = mergeSort(head);
    }

    void print() const {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

// Ejercicio 1: Convertir una lista enlazada binaria a decimal
template <typename T>
int getDecimalValue(Node<T>* head) {
    int result = 0;
    while (head) {
        result = (result << 1) | head->data;
        head = head->next;
    }
    return result;
}

// Ejercicio 2: Encontrar el nodo medio de la lista enlazada
template <typename T>
Node<T>* middleNode(Node<T>* head) {
    Node<T>* slow = head;
    Node<T>* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// Ejercicio 3: Invertir una lista enlazada
template <typename T>
Node<T>* reverseList(Node<T>* head) {
    Node<T>* prev = nullptr;
    Node<T>* current = head;
    while (current) {
        Node<T>* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

// Ejercicio 4: Eliminar duplicados de una lista enlazada ordenada
template <typename T>
Node<T>* deleteDuplicates(Node<T>* head) {
    Node<T>* current = head;
    while (current && current->next) {
        if (current->data == current->next->data) {
            Node<T>* temp = current->next;
            current->next = temp->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
    return head;
}

// Ejercicio 5: Eliminar el nodo n-ésimo desde el final
template <typename T>
Node<T>* removeNthFromEnd(Node<T>* head, int n) {
    Node<T>* dummy = new Node<T>(0);
    dummy->next = head;
    Node<T>* slow = dummy;
    Node<T>* fast = dummy;
    for (int i = 0; i <= n; i++) {
        fast = fast->next;
    }
    while (fast) {
        slow = slow->next;
        fast = fast->next;
    }
    Node<T>* toDelete = slow->next;
    slow->next = slow->next->next;
    delete toDelete;
    Node<T>* newHead = dummy->next;
    delete dummy;
    return newHead;
}

// Ejercicio 6: Detectar palíndromo en una lista enlazada
template <typename T>
bool isPalindrome(Node<T>* head) {
    if (!head || !head->next) return true;

    // Encontrar el medio
    Node<T>* slow = head;
    Node<T>* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Invertir la segunda mitad
    Node<T>* prev = nullptr;
    while (slow) {
        Node<T>* next = slow->next;
        slow->next = prev;
        prev = slow;
        slow = next;
    }

    // Comparar ambas mitades
    Node<T>* left = head;
    Node<T>* right = prev;
    while (right) {
        if (left->data != right->data) return false;
        left = left->next;
        right = right->next;
    }
    return true;
}

int main() {
    // Ejemplo de uso para la forwardList
    forwardList<int> list;
    list.push_back(3);
    list.push_front(1);
    list.push_back(4);
    list.push_back(2);
    list.print(); // 1 -> 3 -> 4 -> 2 -> nullptr

    list.sort();
    list.print(); // 1 -> 2 -> 3 -> 4 -> nullptr

    std::cout << "Size: " << list.size() << std::endl; // 4
    std::cout << "Front: " << list.front() << std::endl; // 1
    std::cout << "Back: " << list.back() << std::endl; // 4

    list.pop_front();
    list.print(); // 2 -> 3 -> 4 -> nullptr

    list.pop_back();
    list.print(); // 2 -> 3 -> nullptr

    list.clear();
    list.print(); // nullptr

    return 0;
}
