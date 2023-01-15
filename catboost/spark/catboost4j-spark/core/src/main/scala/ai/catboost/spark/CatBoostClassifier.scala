package ai.catboost.spark

import org.apache.spark.ml.linalg._
import org.apache.spark.ml.param.ParamMap
import org.apache.spark.ml.classification.{ProbabilisticClassificationModel,ProbabilisticClassifier}
import org.apache.spark.ml.util.Identifiable

import ai.catboost.spark.params._

import ru.yandex.catboost.spark.catboost4j_spark.core.src.native_impl


class CatBoostClassificationModel (
  override val uid: String,
  var nativeModel: native_impl.TFullModel = null,
  var nativeDimension: Int
)
  extends ProbabilisticClassificationModel[Vector, CatBoostClassificationModel]
    with CatBoostModelTrait[CatBoostClassificationModel]
{
  def this(nativeModel : native_impl.TFullModel) = this(
    Identifiable.randomUID("CatBoostClassificationModel"),
    nativeModel,
    nativeModel.GetDimensionsCount.toInt
  )

  override def copy(extra: ParamMap): CatBoostClassificationModel = {
    val newModel = defaultCopy[CatBoostClassificationModel](extra)
    newModel.nativeModel = this.nativeModel
    newModel.nativeDimension = this.nativeDimension
    newModel
  }

  override def numClasses: Int = {
    if (nativeDimension == 1) 2 else nativeDimension
  }

  /**
   * Prefer batch computations operating on datasets as a whole for efficiency
   */
  override protected def predictRaw(features: Vector): Vector = {
    val nativePredictions = predictRawImpl(features)
    if (nativeDimension == 1) {
      Vectors.dense(-nativePredictions(0), nativePredictions(0))
    } else {
      Vectors.dense(nativePredictions)
    }
  }

  /**
   * Prefer batch computations operating on datasets as a whole for efficiency
   */
  override protected def raw2probabilityInPlace(rawPrediction: Vector): Vector = {
    val result = new Array[Double](rawPrediction.size)
    native_impl.native_impl.CalcSoftmax(rawPrediction.toDense.values, result)
    Vectors.dense(result)
  }
}


class CatBoostClassifier (override val uid: String)
  extends ProbabilisticClassifier[Vector, CatBoostClassifier, CatBoostClassificationModel]
    with CatBoostPredictorTrait[CatBoostClassifier, CatBoostClassificationModel, ClassifierTrainingParamsTrait]
{
  def this() = this(Identifiable.randomUID("CatBoostClassifier"))

  override def copy(extra: ParamMap): CatBoostClassifier = defaultCopy(extra)

  protected override def createModel(nativeModel: native_impl.TFullModel): CatBoostClassificationModel = {
    new CatBoostClassificationModel(nativeModel)
  }
}