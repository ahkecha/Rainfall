
class N {
    private:
        int hh;
        char annotation[100]; // bruh
    public:
        N(int a) {
            this->hh = a;
        }
        void setAnnotation(char *s) {
           memcpy(annotation, s, strlen(s));
        }
        int N::operator+(N &a0) {
            return this->hh + a0.hh;
        }
        int N::operator-(N &a0) {
            return this->hh - a0.hh;
        }
}


int main(int ac, char **av)
{
    N *v3; 
    N *v4; 

    if ( ac <= 1 )
    _exit(1);

    v3 = new (5);
    v4 = new (6);

    v3->setAnnotation(av[1]);
    return v3 + v4;
}