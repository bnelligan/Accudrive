
#include <cstdio>
#include "ScoreTracker.h"
#include "SpeedCheck.h"

ScoreTracker::ScoreTracker() {
    scoreMap[SPEEDING] = 250.0;
    scoreMap[PARKING] = 250.0;
    scoreMap[LANE_CHANGE] = 250.0;
    scoreMap[TRAFFIC_SIGNAL] = 250.0;

    scoreWeightMap[SPEEDING] = 50.0;
    scoreWeightMap[PARKING] = 35.0;
    scoreWeightMap[LANE_CHANGE] = 25.0;
    scoreWeightMap[TRAFFIC_SIGNAL] = 100.0;
}

void ScoreTracker::AddScore(ScoreFactor factor) {
    scoreMap[factor] += scoreWeightMap[factor];
    LOGI("Score Increased! New score: %f", scoreMap[factor]);
}

void ScoreTracker::SubtractScore(ScoreFactor factor) {
    scoreMap[factor] -= scoreWeightMap[factor];
    LOGI("Score Lost... New score: %f", scoreMap[factor]);
}

double ScoreTracker::CalcTotalScore() {
    double totalScore = 0.0;
    totalScore += scoreMap[SPEEDING];
    totalScore += scoreMap[PARKING];
    totalScore += scoreMap[LANE_CHANGE];
    totalScore += scoreMap[TRAFFIC_SIGNAL];
    return totalScore;
}

void ScoreTracker::SaveReport() {
    double totalScore = CalcTotalScore();
    char  reportBuff [100];

    std::sprintf(reportBuff, "TotalScore:%f\nSpeed Score:%f\nParking:%f\nLane Change:%f\nTraffic Signal:%f\n",
            totalScore, scoreMap[SPEEDING], scoreMap[PARKING], scoreMap[LANE_CHANGE], scoreMap[TRAFFIC_SIGNAL]);
    std::string reportString = reportBuff;

    std::ofstream reportOutput;
    reportOutput.open("/data/data/com.accudrive.app/report.txt");
    reportOutput << reportString;
    reportOutput.close();
}

