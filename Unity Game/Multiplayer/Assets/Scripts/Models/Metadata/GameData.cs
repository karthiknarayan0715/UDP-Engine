namespace Models.MetaData
{
    public class GameData
    {
        private string gameId;

        public GameData(string gameId)
        {
            this.gameId = gameId;
        }
        
        public string getGameId () => gameId;
    }
}