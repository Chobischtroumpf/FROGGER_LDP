# include "Frog.hpp"

Frog::Frog(Point start_pos): Rectangle{{start_pos.x*50, start_pos.y*50}, 30, 30},
                             coordinates{start_pos} {}

void Frog::setCurrentCell(Cell<Rectangle> cell) {
    this->currentCell = &cell;
}

Cell<Rectangle>* Frog::getCurrentCell() {
    return this->currentCell;
}

void Frog::keyPressed(int keyCode) {
    if (keyCode == FL_Up || keyCode == 'w' || keyCode == 'z'){
        if (this->coordinates.y < 13) {
            setY(this->coordinates.y + 1);
        }
    } else if (keyCode == FL_Down || keyCode == 's') {
        if (this->coordinates.y > 0) {
            setY(this->coordinates.y - 1);
        }
    } else if (keyCode == FL_Left || keyCode == 'a' || keyCode == 'q') {
        if (this->coordinates.x < 13) {
            setX(this->coordinates.x + 1);
        }
    } else if (keyCode == FL_Right || keyCode == 'd') {
        if(this->coordinates.x > 0) {
            setX(this->coordinates.x -1);
        }
    }
}

void Frog::print(){
    Frog::Rectangle::print();
}