class Button {
    public:
        Button(int pin);
        bool clicked(void);
    private:
        int pin;
        bool pressed;
};
