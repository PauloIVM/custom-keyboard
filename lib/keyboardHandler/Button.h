class Button {
    public:
        Button(int pin, void (*onPress)(void), void (*onRelease)(void));
        void exec(void);
        void begin(void);
    private:
        int pin;
        bool state;
        bool pressed(void);
        bool released(void);
        void (*onPress)(void);
        void (*onRelease)(void);
};
