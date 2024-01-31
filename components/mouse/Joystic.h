class Joystic {
    public:
        Joystic(int xPin, int yPin, int xAnalogCenter, int yAnalogCenter);
        int readX(void);
        int readY(void);
        void toggleRange(void);
        void setRange(int range);
    private:
        int read(int pin, int analogCenter);
        int threshold;
        int range;
        int xPin;
        int yPin;
        int xAnalogCenter;
        int yAnalogCenter;
};
