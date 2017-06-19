#ifndef ABSTRACTREADERWRITER_H
#define ABSTRACTREADERWRITER_H

/**
 * @brief Classe abstraite du protocole lecteur rédacteur
 *        définit les méthodes à implémenter dans les protocoles
 *        concrets.
 */
class AbstractReaderWriter {
public:
    /**
     * @brief Constructeur
     */
    AbstractReaderWriter();

    /**
     * @brief Destructeur
     */
    virtual ~AbstractReaderWriter();

    /**
     * @brief lockReading - vérouille l'accès pour le lecteur
     */
    virtual void lockReading() = 0;
    virtual void lockWriting() = 0;
    virtual void unlockReading() = 0;
    virtual void unlockWriting() = 0;
};

#endif // ABSTRACTREADERWRITER_H
