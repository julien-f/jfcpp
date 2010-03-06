/**
 * Ce fichier propose des macros afin de simplifier et de formaliser l'écriture
 * de programmes C/C++ avec le paradigme de programmation par contrats.
 *
 * Copyleft 2010 - Julien Fontanet <julien.fontanet@isonoe.net>
 *
 * v1.3 - 2010-02-23
 * - Nouvelle macro pour C++ : assert_exception qui assure qu'une exception d'un
 *   certain type est levée lorsqu'un bout de code est executé (utile pour les
 *   jeux de tests).
 *
 * v1.2 - 2010-02-09
 * - Si la macro EXDEBUG est définie en plus de DEBUG alors les macros ensures,
 *   requires et validate n'interrompent plus l'exécution du programme en cas
 *   d'erreur mais lèvent une exception de type ContractViolated.
 * - debug_stmt a été renommé en debug_code.
 *
 * v1.1 - 2010-01-27
 * -  Un destructeur virtuel a été ajouté à la classe CertifiedObject.
 */

#ifndef H_CONTRACTS
#define H_CONTRACTS

#ifdef __cplusplus
#  include <cassert>
#else
#  include <assert.h>
#endif

#ifdef NDEBUG
#  define CONTRATS_ASSERT(expr) ((void) 0)
#  define debug_code(code) ((void) 0)
#elif defined(EXDEBUG) && defined(__cplusplus)
#  define CONTRATS_ASSERT(expr) ((expr) ? (void) 0 : throw ContractViolated(#expr))
#else
#  define CONTRATS_ASSERT(expr) assert(expr)
#endif

#ifndef NDEBUG
/**
 * Permet d'écrire du code qui ne sera exécuté que si l'on est en mode débogage.
 *
 * Ce code peut-être utile pour des pré-conditions où des post-conditions.
 *
 * Exemples :
 *   debug_code(int solde = this->solde);
 *   ensures(this->solde = solde + montant);
 */
#define debug_code(code) code
#endif

/**
 * Cette macro permet de spécifier une pré-condition, c'est-à-dire une condition
 * nécessaire pour que la fonction/méthode s'éxecute correctement.
 *
 * Exemple :
 *   requires(solde > 0);
 */
#define requires(exp) (CONTRATS_ASSERT(exp))

/**
 * Cette macro permet de spécifier une post-condition, c'est-à-dire une
 * condition qui doit être vrai à la fin de la fonction/méthode.
 *
 * Exemple :
 *   ensures(solde > 0);
 */
#define ensures(exp) (CONTRATS_ASSERT(exp))


// Définitions supplémentaires pour le C++


#ifdef __cplusplus

#include <stdexcept>

/**
 * Tout objet descendant de celui-ci doit fournir une implémentation de la
 * méthode isValid().
 */
class CertifiedObject
{
public:
	/**
	 * Destructeur virtuel, nécessaire pour l'appel en chaîne des destructeurs.
	 */
	virtual ~CertifiedObject() {}

	/**
	 * Vérifie que les invariants de classe sont respectés.
	 *
	 * @return true si les invariants de classe sont respectés, c'est-à-dire que
	 *         l'état courant de l'objet est correct, false sinon.
	 */
	virtual bool isValid() const =0;
};

/**
 * Quand la macro EXDEBUG est définie en plus de DEBUG, les macros validate,
 * ensures, requires n'arrêtent plus le programme mais lancent une exception de
 * ce type.
 */
class ContractViolated : public std::logic_error
{
public:
	/**
	 * Construit une intance de ContractViolated qui indique qu'un contrat dans
	 * le code n'a pas été respecté.
	 *
	 * @param what La condition qui n'a pas été respectée.
	 */
	explicit ContractViolated(const std::string &what) : logic_error(what) {}
};

/**
 * Cette macro assure que les invariants de classe d'un objet de type
 * CertifiedObject ou dérivé soit respectés.
 *
 * Exemple :
 *   validate(*this);
 *
 * @param object L'objet à vérifier.
 */
#define validate(object) (CONTRATS_ASSERT((object).isValid()))

/**
 * Cette macro assure que l'exécution du code 'code' lève une exception de type
 * 'ex'.
 *
 * @param code Le code à exécuter.
 * @param ex   Le type de l'exception qui doit être levée.
 */
#define assert_exception(code, ex) \
	if (true) \
		try {code; assert(false);} \
		catch (ex) {} \
		catch (...) {assert(false);} \
	else ((void) 0)

#endif // __cplusplus

#endif // H_CONTRACTS
