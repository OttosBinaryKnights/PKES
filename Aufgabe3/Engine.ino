void InitEngines()
{
    DDRH |= ( 1 << 3 );
    DDRH |= ( 1 << 4 );
    DDRB |= ( 1 << 5 );
    DDRB |= ( 1 << 6 );

    ICR1   = 255; // Set top for timer 1
    //FastPWM non-inverting mode
    TCCR1A = ( 1 << COM1A1 ) | ( 1 << COM1B1 ) | ( 1 << WGM11 );  
    TCCR1B = ( 1 << WGM13  ) | ( 1 << WGM12 ) | ( 1 << CS10 );
    OCR1A  = 0; // Power FWD Left
    OCR1B  = 0; // Power RWD Left

    ICR4   = 255; // Set top for timer 4
    TCCR4A = ( 1 << COM1A1 ) | ( 1 << COM1B1 ) | ( 1 << WGM11 );
    TCCR4B = ( 1 << WGM13  ) | ( 1 << WGM12 ) | ( 1 << CS10 );
    OCR4A  = 0; // Power FWD Right
    OCR4B  = 0; // Power RWD Right
}
