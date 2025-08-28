using System;

namespace Models.Message.Client
{
    public class ClientHeadersInfo
    {
        private int contentLength;
        private String contentType;
        
        public ClientHeadersInfo(String contentType, int contentLength) {
            this.contentLength = contentLength;
            this.contentType = contentType;
        }

        public int getContentLength() {
            return contentLength;
        }

        public void setContentLength(int contentLength) {
            this.contentLength = contentLength;
        }

        public String getContentType() {
            return contentType;
        }

        public void setContentType(String contentType) {
            this.contentType = contentType;
        }

        public String getHeaders() {

            return Constants.CONTENT_LENGTH + Constants.COLON + this.getContentLength() + Constants.HEADER_SEPARATOR + Constants.CONTENT_TYPE + Constants.COLON + this.getContentType() + Constants.HEADER_DELIMITER;
        }
    }
}