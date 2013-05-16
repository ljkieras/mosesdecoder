#ifndef moses_WordTranslationFeature_h
#define moses_WordTranslationFeature_h

#include <string>
#include <boost/unordered_set.hpp>

#include "FeatureFunction.h"
#include "FactorCollection.h"

#include "Sentence.h"
#include "FFState.h"

namespace Moses
{

/** Sets the features for word translation
 */
class WordTranslationFeature : public StatelessFeatureFunction {

  typedef std::map< char, short > CharHash;
  typedef std::vector< boost::unordered_set<std::string> > DocumentVector;
	
private:
  boost::unordered_set<std::string> m_vocabSource;
  boost::unordered_set<std::string> m_vocabTarget;
  DocumentVector m_vocabDomain;
  FactorType m_factorTypeSource;
  FactorType m_factorTypeTarget;
  bool m_unrestricted;
  bool m_simple;
  bool m_sourceContext;
  bool m_targetContext;
  bool m_domainTrigger;
  bool m_ignorePunctuation;
  CharHash m_punctuationHash;
  
public:
  WordTranslationFeature(const std::string &line);
  
  bool Load(const std::string &filePathSource, const std::string &filePathTarget);
  
  const FFState* EmptyHypothesisState(const InputType &) const {
    return new DummyState();
  }
  
  void Evaluate(const PhraseBasedFeatureContext& context,                       
		ScoreComponentCollection* accumulator) const;

  void EvaluateChart(const ChartBasedFeatureContext& context,
                     ScoreComponentCollection* accumulator) const;
  
  virtual void Evaluate(const TargetPhrase &targetPhrase
                      , ScoreComponentCollection &scoreBreakdown
                      , ScoreComponentCollection &estimatedFutureScore) const;

  StatelessFeatureType GetStatelessFeatureType() const
  { return RequiresSegmentation; }
};

}

#endif // moses_WordTranslationFeature_h
