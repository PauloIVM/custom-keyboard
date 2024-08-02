class Button {
    public:
        Button(int pin);
        bool pressed(void);
        bool released(void);
    private:
        int pin;
        bool state;
};
