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

    /**
     * @brief lockWriting - vérouille l'accès pour le rédacteur
     */
    virtual void lockWriting() = 0;

    /**
     * @brief unlockReading - un lecteur dévérouille l'accès
     */
    virtual void unlockReading() = 0;

    /**
     * @brief unlockWriting - un rédacteur dévérouille l'accès
     */
    virtual void unlockWriting() = 0;
};

#endif // ABSTRACTREADERWRITER_H
