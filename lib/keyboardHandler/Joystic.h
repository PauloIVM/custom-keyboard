class Joystic {
    public:
        Joystic(int xPin, int yPin, int xAnalogCenter, int yAnalogCenter, void (*onChange)(int x, int y));
        void exec(void);
        void setRange(int range);
    private:
        int readX(void);
        int readY(void);
        int read(int pin, int analogCenter);
        int threshold;
        int range;
        int xPin;
        int yPin;
        int xAnalogCenter;
        int yAnalogCenter;
        void (*onChange)(int x, int y);
};
