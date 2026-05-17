import sys
from dataclasses import dataclass
from typing import List

@dataclass
class Rule:
    conditions: List[int]
    signal: str
    recommendation: str
    min_score: int

def ask_yes_no(question):
    """Ask Yes/No Question"""
    while True:
        ans = input(f"{question} (Y/N): ").strip().upper()
        if ans in ['Y', 'N']:
            return ans == 'Y'
        print("Enter Y or N: ", end="")

def calculate_technical_score(facts):
    """Calculate score based on technical indicators"""
    score = 0
    
    # Moving Average Crossover 
    if facts[1]:
        score += 20
    
    # RSI Signal  - Overbought/Oversold
    if facts[2]:
        score += 15
    
    # Volume Spike 
    if facts[3]:
        score += 10
    
    # Support/Resistance Breakout 
    if facts[4]:
        score += 15
    
    return score

def calculate_momentum_score(facts: List[bool]) -> int:
    """Calculate score based on momentum indicators"""
    score = 0
    
    # Positive Trend 
    if facts[5]:
        score += 20
    
    # MACD Signal 
    if facts[6]:
        score += 15
    
    # Price Momentum 
    if facts[7]:
        score += 10
    
    return score

def calculate_risk_score(facts: List[bool]) -> int:
    """Calculate score based on risk factors - negative impact"""
    risk_penalty = 0
    
    # High Volatility - reduces confidence
    if facts[8]:
        risk_penalty += 15
    
    # Economic Uncertainty - reduces confidence
    if facts[9]:
        risk_penalty += 20
    
    # Bearish News - reduces confidence
    if facts[10]:
        risk_penalty += 25
    
    # Earnings Report Coming - adds uncertainty
    if facts[11]:
        risk_penalty += 10
    
    return risk_penalty

def calculate_portfolio_score(facts: List[bool]) -> int:
    """Calculate score based on portfolio context"""
    score = 0
    
    # Portfolio Diversified 
    if facts[12]:
        score += 10
    
    # Cash Available 
    if facts[13]:
        score += 10
    
    return score

def main():
    print("=" * 50)
    print(" STOCK MARKET TRADING EXPERT SYSTEM")
    print("=" * 50)
    print()
    
    # FACT STORAGE
    facts = [False] * 14
    
    # ASK QUESTIONS
    print("TECHNICAL ANALYSIS QUESTIONS:\n")
    facts[0] = ask_yes_no("1. Is the stock price in an uptrend?")
    facts[1] = ask_yes_no("2. Has the short-term MA crossed above long-term MA?")
    facts[2] = ask_yes_no("3. Is RSI in the 30-70 range (not overbought/oversold)?")
    facts[3] = ask_yes_no("4. Is there a volume spike with price movement?")
    facts[4] = ask_yes_no("5. Has the stock broken above key resistance level?")
    
    print("\nMOMENTUM INDICATORS:\n")
    facts[5] = ask_yes_no("6. Is the overall market trend positive?")
    facts[6] = ask_yes_no("7. Is MACD showing bullish crossover?")
    facts[7] = ask_yes_no("8. Is price momentum accelerating upward?")
    
    print("\nRISK FACTORS:\n")
    facts[8] = ask_yes_no("9. Is volatility unusually high?")
    facts[9] = ask_yes_no("10. Is there economic uncertainty in the market?")
    facts[10] = ask_yes_no("11. Are there bearish news about the stock?")
    facts[11] = ask_yes_no("12. Are earnings or major news coming soon?")
    
    print("\nPORTFOLIO CONTEXT:\n")
    facts[12] = ask_yes_no("13. Is your portfolio well diversified?")
    facts[13] = ask_yes_no("14. Do you have sufficient cash for investment?")
    
    # CALCULATE SCORES
    technical_score = calculate_technical_score(facts)
    momentum_score = calculate_momentum_score(facts)
    risk_penalty = calculate_risk_score(facts)
    portfolio_score = calculate_portfolio_score(facts)
    
    # Net Score Calculation
    total_score = technical_score + momentum_score + portfolio_score - risk_penalty
    total_score = max(0, min(100, total_score)) 
    

    # DEFINE RULES. (Class defined above)
    rules = [
        # Strong Buy Signal
        Rule(
            conditions=[0, 1, 2, 3, 4, 5, 6, 7],
            signal="STRONG BUY",
            recommendation="Consider buying with full position. Multiple indicators are aligned.",
            min_score=75
        ),
        # Buy Signal
        Rule(
            conditions=[1, 5, 6],
            signal="BUY",
            recommendation="Good opportunity to buy. Technical indicators are positive.",
            min_score=60
        ),
        # Moderate Buy
        Rule(
            conditions=[0, 5],
            signal="MODERATE BUY",
            recommendation="Consider a small position. Market trend is positive.",
            min_score=50
        ),
        # Hold Signal
        Rule(
            conditions=[2],
            signal="HOLD",
            recommendation="Stock is in neutral zone. Wait for clearer signals.",
            min_score=40
        ),
        # Sell Signal
        Rule(
            conditions=[-5, -6, 8, 9],
            signal="SELL",
            recommendation="Risk factors are high. Consider reducing position.",
            min_score=25
        ),
        # Strong Sell
        Rule(
            conditions=[10, 8],
            signal="STRONG SELL",
            recommendation="High risk detected. Close position immediately.",
            min_score=0
        ),
    ]


    print("\n" + "=" * 50)
    print(" TRADING ANALYSIS RESULTS")
    print("=" * 50)
    print()
    
    print(f"Technical Score: {technical_score}/70")
    print(f"Momentum Score: {momentum_score}/45")
    print(f"Portfolio Score: {portfolio_score}/20")
    print(f"Risk Penalty: -{risk_penalty}/70")
    print(f"\nOVERALL SCORE: {total_score}/100")
    print()
    
    found = False
    
    for rule in rules:
        match = True
        
        for cond in rule.conditions:
            if cond >= 0:
                if not facts[cond]:
                    match = False
                    break
            else:
                if facts[-cond]:
                    match = False
                    break
        
        if match and total_score >= rule.min_score:
            found = True
            print(f"SIGNAL: {rule.signal}")
            print(f"Confidence Level: {total_score}%")
            print(f"Recommendation: {rule.recommendation}")
            print()
            break
    
    if not found:
        if total_score > 50:
            print("SIGNAL: HOLD")
            print(f"Confidence Level: {total_score}%")
            print("Recommendation: Insufficient signals for trading decision. Continue monitoring.")
        else:
            print("SIGNAL: NO CLEAR SIGNAL")
            print(f"Confidence Level: {100 - total_score}%")
            print("Recommendation: Market conditions are unclear. Avoid trading until signals improve.")

if __name__ == "__main__":
    main()
