用dp[next_state] = min(dp[state] + 1, dp[next_state]);

这里我们的需要计算next state 并且把结果保存，state表示 当前的target 已经有哪些字符了，并且所需的最少stickers。 

之所以把这题写下来，是因为很久没有把next state 当成主语，很多事时候都是 当前状态 从 前面床过来， 现在变成，当前状态可以推出的所有状态。