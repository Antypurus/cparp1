using Microsoft.VisualBasic.CompilerServices;

namespace CSharpPerformanceAnalysis
{
    public class SerialMatrix
    {
        private float[] m_matrix;
        private int width;
        private int height;

        private int algorithm = 0; //0 -> standard algo, 1 -> line based algorithm, 2 -> block algorithm

        private int BLOCK_SIZE;

        public SerialMatrix(int width, int height, bool iterativeStart, int algorithm, int blockSize)
        {
            this.m_matrix = new float[width * height];
            int iter = 1;
            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    if (iterativeStart)
                    {
                        m_matrix[i * height + j] = iter;
                    }
                    else
                    {
                        m_matrix[i * height + j] = 1;
                    }
                }

                if (iterativeStart)
                {
                    iter++;
                }
            }
            this.height = height;
            this.width = width;
            this.algorithm = algorithm;
            this.BLOCK_SIZE = blockSize;
        }

        public void setData(float[] data)
        {
            this.m_matrix = data;
        }

        public ref float getValue(int y, int x)
        {
            return ref this.m_matrix[y * this.width + x];
        }

        public static SerialMatrix operator *(SerialMatrix A, SerialMatrix B)
        {
            float[] retData = new float[A.height * A.width];
            for (int i = 0; i < retData.Length; ++i)
            {
                retData[i] = 0;
            }
            SerialMatrix ret = new SerialMatrix(A.width,A.height,false,A.algorithm,A.BLOCK_SIZE);

            //multiplication
            {
                if (A.algorithm == 0)
                {
                    for (int i = 0; i < A.height; ++i)
                    {
                        for (int j = 0; j < B.width; ++j)
                        {
                            for (int k = 0; k < B.height; ++k)
                            {
                                retData[i * A.height + j] += A.getValue(i, k) * B.getValue(k, j);
                            }
                        }
                    }
                }
                else if (A.algorithm == 1)
                {
                    for (int i = 0; i < A.height; ++i)
                    {
                        for (int k = 0; k < B.height; ++k)
                        {
                            for (int j = 0; j < B.width; ++j)
                            {
                                retData[i * A.height + j] += A.getValue(i, k) * B.getValue(k, j);
                            }

                        }
                    }
                }
                else if(A.algorithm == 2)
                {
                    for (int ii = 0; ii < A.height; ii += A.BLOCK_SIZE)
                    {
                        for (int kk = 0; kk < B.width; kk += A.BLOCK_SIZE)
                        {
                            for (int jj = 0; jj < B.height; jj += A.BLOCK_SIZE)
                            {
                                for (int i = ii; i < ii + A.BLOCK_SIZE && i < A.height; i++)
                                {
                                    for (int k = kk; k < kk + A.BLOCK_SIZE && k < B.width; k++)
                                    {
                                        for (int j = jj; j < jj + A.BLOCK_SIZE && j < B.height; j++)
                                        {
                                            retData[i * A.height + j] += A.getValue(i, k) * B.getValue(k, j);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            ret.setData(retData);
            return ret;
        }

    }
}