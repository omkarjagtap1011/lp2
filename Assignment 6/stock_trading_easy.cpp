#include <iostream>
#include <string>
using namespace std;

// Function to ask Yes/No questions
bool askYesNo(string question) {
    char ans;
    while (true) {
        cout << question << " (Y/N): ";
        cin >> ans;
        ans = toupper(ans);
        if (ans == 'Y' || ans == 'N') {
            return ans == 'Y';
        }
        cout << "Enter Y or N: ";
    }
}

// Function to calculate technical score
int calculateTechnicalScore(bool facts[]) {
    int score = 0;
    
    if (facts[0]) score += 10;  // Trend
    if (facts[1]) score += 20;  // Moving Average Crossover
    if (facts[2]) score += 15;  // RSI Signal
    if (facts[3]) score += 10;  // Volume Spike
    if (facts[4]) score += 15;  // Support/Resistance Breakout
    
    return score;
}

// Function to calculate momentum score
int calculateMomentumScore(bool facts[]) {
    int score = 0;
    
    if (facts[5]) score += 20;  // Positive Trend
    if (facts[6]) score += 15;  // MACD Signal
    if (facts[7]) score += 10;  // Price Momentum
    
    return score;
}

// Function to calculate risk penalty
int calculateRiskScore(bool facts[]) {
    int risk = 0;
    
    if (facts[8])  risk += 15;  // High Volatility
    if (facts[9])  risk += 20;  // Economic Uncertainty
    if (facts[10]) risk += 25;  // Bearish News
    if (facts[11]) risk += 10;  // Earnings Report Coming
    
    return risk;
}

// Function to calculate portfolio score
int calculatePortfolioScore(bool facts[]) {
    int score = 0;
    
    if (facts[12]) score += 10;  // Portfolio Diversified
    if (facts[13]) score += 10;  // Cash Available
    
    return score;
}

// Normalize a raw score into the 0-1 range based on its possible minimum and maximum.
double normalizeScore(int rawScore, int minRawScore, int maxRawScore) {
    if (maxRawScore <= minRawScore) {
        return 0.0;
    }

    double normalizedScore = static_cast<double>(rawScore - minRawScore) /
                             static_cast<double>(maxRawScore - minRawScore);

    return normalizedScore;
}


int main() {
    cout << "================================================" << endl;
    cout << " STOCK MARKET TRADING EXPERT SYSTEM (EASY)" << endl;
    cout << "================================================" << endl << endl;
    
    // Array to store facts (answers)
    bool facts[14];
    
    // Ask questions - Technical Analysis
    cout << "TECHNICAL ANALYSIS QUESTIONS:\n" << endl;
    facts[0] = askYesNo("1. Is the stock price in an uptrend?");
    facts[1] = askYesNo("2. Has the short-term MA crossed above long-term MA?");
    facts[2] = askYesNo("3. Is RSI in the 30-70 range (not overbought/oversold)?");
    facts[3] = askYesNo("4. Is there a volume spike with price movement?");
    facts[4] = askYesNo("5. Has the stock broken above key resistance level?");
    
    // Ask questions - Momentum Indicators
    cout << "\nMOMENTUM INDICATORS:\n" << endl;
    facts[5] = askYesNo("6. Is the overall market trend positive?");
    facts[6] = askYesNo("7. Is MACD showing bullish crossover?");
    facts[7] = askYesNo("8. Is price momentum accelerating upward?");
    
    // Ask questions - Risk Factors
    cout << "\nRISK FACTORS:\n" << endl;
    facts[8] = askYesNo("9. Is volatility unusually high?");
    facts[9] = askYesNo("10. Is there economic uncertainty in the market?");
    facts[10] = askYesNo("11. Are there bearish news about the stock?");
    facts[11] = askYesNo("12. Are earnings or major news coming soon?");
    
    // Ask questions - Portfolio Context
    cout << "\nPORTFOLIO CONTEXT:\n" << endl;
    facts[12] = askYesNo("13. Is your portfolio well diversified?");
    facts[13] = askYesNo("14. Do you have sufficient cash for investment?");
    
    // Calculate scores
    int technicalScore = calculateTechnicalScore(facts);
    int momentumScore = calculateMomentumScore(facts);
    int riskPenalty = calculateRiskScore(facts);
    int portfolioScore = calculatePortfolioScore(facts);
    
    int rawScore = technicalScore + momentumScore + portfolioScore - riskPenalty;
    double normalizedScore = normalizeScore(rawScore, -70, 135);
    int totalScore = normalizedScore * 100;
    
    // Display results
    cout << "\n================================================" << endl;
    cout << " TRADING ANALYSIS RESULTS" << endl;
    cout << "================================================" << endl << endl;
    
    cout << "Technical Score: " << technicalScore << "/60" << endl;
    cout << "Momentum Score: " << momentumScore << "/45" << endl;
    cout << "Portfolio Score: " << portfolioScore << "/20" << endl;
    cout << "Risk Penalty: -" << riskPenalty << "/70" << endl;
    cout << "\nOVERALL SCORE: " << totalScore << "/100" << endl << endl;
    
    // Generate trading signal
    string signal;
    string recommendation;
    
    // Rule 1: Strong Buy (all indicators positive + high score)
    if (facts[0] && facts[1] && facts[2] && facts[3] && facts[4] && 
        facts[5] && facts[6] && facts[7] && totalScore >= 75) {
        signal = "STRONG BUY";
        recommendation = "Consider buying with full position. Multiple indicators are aligned.";
    }
    // Rule 2: Buy (key indicators positive)
    else if (facts[1] && facts[5] && facts[6] && totalScore >= 60) {
        signal = "BUY";
        recommendation = "Good opportunity to buy. Technical indicators are positive.";
    }
    // Rule 3: Moderate Buy
    else if (facts[0] && facts[5] && totalScore >= 50) {
        signal = "MODERATE BUY";
        recommendation = "Consider a small position. Market trend is positive.";
    }
    // Rule 4: Hold
    else if (facts[2] && totalScore >= 40) {
        signal = "HOLD";
        recommendation = "Stock is in neutral zone. Wait for clearer signals.";
    }
    // Rule 5: Sell (risk factors present)
    else if (facts[8] && facts[9] && totalScore <= 25) {
        signal = "SELL";
        recommendation = "Risk factors are high. Consider reducing position.";
    }
    // Rule 6: Strong Sell (bearish signals)
    else if (facts[10] && facts[8]) {
        signal = "STRONG SELL";
        recommendation = "High risk detected. Close position immediately.";
    }
    // Default: No Clear Signal
    else {
        if (totalScore > 50) {
            signal = "HOLD";
            recommendation = "Insufficient signals for trading decision. Continue monitoring.";
        } else {
            signal = "NO CLEAR SIGNAL";
            recommendation = "Market conditions are unclear. Avoid trading until signals improve.";
        }
    }
    
    // Display trading signal
    cout << "SIGNAL: " << signal << endl;
    cout << "Confidence Level: " << totalScore << "%" << endl;
    cout << "Recommendation: " << recommendation << endl;
    
    return 0;
}
