
DynamicArray::DynamicArray() : capacity(1), size(0) {
    actors = new Actor*[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] actors;
}

void DynamicArray::resize() {
    int newCapacity = capacity * 2;
    Actor** newArray = new Actor*[newCapacity];
    for (int i = 0; i < size; ++i) {
        newArray[i] = actors[i];
    }
    delete[] actors;
    actors = newArray;
    capacity = newCapacity;
}

Actor* DynamicArray::get(int index) {
    if (index < 0 || index >= size) {
        return nullptr;
    }
    return actors[index];
}

void DynamicArray::add(Actor* actor) {
    for (int i = 0; i < size; ++i) {
        if (actors[i]->getName() == actor->getName()) {
            return;  // Actor already present, do not add
        }
    }
    if (size == capacity) {
        resize();
    }
    actors[size++] = actor;
}

int DynamicArray::getSize() const {
    return size;
}
