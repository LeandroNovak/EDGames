template<class T>
class StaticStack
{
public:
	StaticStack();
	StaticStack(int);
	~StaticStack();
	bool push(T item);
	T pop();
	bool isFull();
	bool isEmpty();
	T getTop();

private:
	int max;
	T * node;
	int top;
};

// Construtor de pilha padrão
template<class T>
StaticStack<T>::StaticStack()
{
	node = new T[DEFAULTSIZE];
	top = -1;
	max = DEFAULTMAX - 1;
}

// Construtor de pilha com tamanho definido pelo usuário
template<class T>
StaticStack<T>::StaticStack(int size)
{
	node = new T[size];
	top = -1;
	max = size - 1;
}

// Destrutor de pilha
template<class T>
StaticStack<T>::~StaticStack()
{
	if (node != nullptr)
		delete[] node;
}

// Push, adiciona item no topo da pilha
template<class T>
bool StaticStack<T>::push(T item)
{
	if (top < max) 
	{
		top++;
		node[top] = item;
		return true;
	}
	else
		return false;
}

// Pop, remove item do topo da pilha.
template<class T>
T StaticStack<T>::pop()
{
	if (top >= 0) 
	{
		int temp = top;
		top--;
		return node[temp];
	}
}

// Verifica se a pilha está cheia.
template<class T>
bool StaticStack<T>::isFull()
{
	if (top == max)
		return true;
	else
		return false;
	//return (top == max) ? true : false;
}

// Verifica se a pilha está vazia.
template<class T>
bool StaticStack<T>::isEmpty()
{
	if (top == -1)
		return true;
	else
		return false;
	//return (top == -1) ? true : false;
}

// Retorna o item presente no topo da pilha.
template<class T>
T StaticStack<T>::getTop()
{
	return node[top];
}
